import sys
from pathlib import Path
import re
import os
import datetime
import utils.parsingTools as tools


class GeneratedMember :
    name = ""
    type = ""

    def __init__(self, type, name):
        self.type = type
        self.name = name

    def debug(self):
        print("\\t{} {}".format(self.type, self.name))

    def isValid(self):
        return len(self.type) > 0 and len(self.name) > 0
    
    def generateDeserialize(self, file):
        file.write("\tif(name == \"{}\") \\\n".format(self.name))
        file.write("\t\tstd::visit(Deserializer<{}>{{ &a_this.{} }}, data); \\\n".format(self.type, self.name))

#-----------------------------------------------------------------------------
# used for int represented a flag
class GeneratedFlag(GeneratedMember):
    def __init__(self, type, name, baseType):
        GeneratedMember.__init__(self, type, name)
        self.baseType = baseType

    def debug(self):
        print("\\t{} {} Flag<{}>".format(self.type, self.name, self.baseType))

    def generateDeserialize(self, file):
        file.write("\tif(name == \"{}\") \\\n".format(self.name))
        file.write("\t\tstd::visit(FlagDeserializer<{}, {}>{{ &a_this.{} }}, data); \\\n".format(self.type, self.baseType, self.name))
        
#-----------------------------------------------------------------------------

class GeneratedClass :
    def __init__(self, name):
        self.classname = name
        self.members = []
    
    def debug(self):
        print(self.classname)
        for member in self.members :
            member.debug()

    def generateDeserialize(self, file):
        # implements class/struct deserialization
        file.write("/* class deserialization macro */\n")
        file.write("#define _DESERIALIZE_{} \\\n".format(self.classname))
        file.write("for(const auto&[name, data] : a_serialized) \\\n")
        file.write("{ \\\n")
        for member in self.members :
            member.generateDeserialize(file)
        file.write("}\\\n\n")

#-----------------------------------------------------------------------------

class HeaderParser :
    # constant macros names
    MACRO_REFLECT_CLASS = "REFLECT_CLASS"
    MACRO_REFLECT_MEMBER = "REFLECT_MEMBER"
    MACRO_REFECT_FLAG = "REFLECT_FLAG"

    def isReflectClass(self, line):
        return line.startswith(self.MACRO_REFLECT_CLASS)

    def isReflectMember(self, line):
        return line.startswith(self.MACRO_REFLECT_MEMBER)
    
    def isReflectFlag(self, line):
        return line.startswith(self.MACRO_REFECT_FLAG)

    def extractArg(self, line):
        return re.search(".*\\((.*)\\).*", line).group(1)
    
    def appendMember(self, type, name, other):
        self.classList[self.classIndex].members.append(GeneratedMember(type, name))

    def appendMemberFlag(self, type, name, other):
        self.classList[self.classIndex].members.append(GeneratedFlag(type, name, other))

    def getMember(self, file, appendFun, baseType = None):
        found = False
        while not file.atEnd() and not found:
            line = tools.removeComments(file, file.nextTrimmedLine())            
            member = re.search("(.*) (.*);.*", line)
            if "=" in line : 
                member = re.search("(.*)\\s(.+)=(.*);.*", line)
            if member is not None:
                appendFun(member.group(1), member.group(2).strip(), baseType)
                found = True
    
    def getMembers(self, file, classname):
        self.classList.append(GeneratedClass(classname))
        self.classIndex += 1 #current class index
        classBracket = tools.BracketCounter()
        while not file.atEnd() and not classBracket.closed():
            line = tools.removeComments(file, file.nextTrimmedLine())
            classBracket.countBracket(line)
            if self.isReflectMember(line):
                self.getMember(file, self.appendMember)
            elif self.isReflectFlag(line):
                flagBaseType = self.extractArg(line)
                self.getFlag(file, self.appendMemberFlag, flagBaseType)

    def processLine(self, file, curLine):
        if self.isReflectClass(curLine):
            classname = self.extractArg(curLine)
            self.getMembers(file, classname)
    
    def processHeader(self):
        file = tools.TextFile(self.filePath)
        while not file.atEnd():
            line = file.nextTrimmedLine()
            self.processLine(file, line)

    def __init__(self, filePath):
        #print("Parse file: {}".format(filePath))
        self.filePath = filePath
        self.classList = []
        self.classIndex = -1

    def stats(self):
        numClass = len(self.classList)
        if numClass == 0:
            print("File {} > no reflect class/struct".format(self.filePath))
        else:
            print("File {} > {} reflect class/struct".format(self.filePath, numClass))


    def generateHeader(self):
        if len(self.classList) > 0:
            name = os.path.basename(self.filePath)
            name = name[0:len(name) - 1] + "generated.h"
            generatedFile = self.filePath.parent.absolute().__str__() + "\\\\" + name
            file = open(generatedFile, 'w')
            dateNow = datetime.date.today()
            file.write("#pragma once\n")
            file.write("/***********************************************\n")
            file.write("* @headerfile {}\n".format(name))
            file.write("* @date {}/{}/{}\n".format(dateNow.day, dateNow.month, dateNow.year))
            file.write("* @author reflecGen.py\n")
            file.write("************************************************/\n")
            file.write("#include <variant>\n")
            file.write("#include \"DeserializeManager.h\"\n")
            file.write("#include \"Deserializer.h\"\n\n")
            for classParsed in self.classList:
                classParsed.generateDeserialize(file)

    def debug(self):
        print(self.filePath)
        print(os.path.basename(self.filePath))
        for classe in self.classList:
            classe.debug()


#-----------------------------------------------------------------------------

print("    ____  ______________    __________________   _____________   ____________  ___  __________  ____ ")
print("   / __ \\/ ____/ ____/ /   / ____/ ____/_  __/  / ____/ ____/ | / / ____/ __ \\/   |/_  __/ __ \\/ __ \\")
print("  / /_/ / __/ / /_  / /   / __/ / /     / /    / / __/ __/ /  |/ / __/ / /_/ / /| | / / / / / / /_/ /")
print(" / _, _/ /___/ __/ / /___/ /___/ /___  / /    / /_/ / /___/ /|  / /___/ _, _/ ___ |/ / / /_/ / _, _/ ")
print("/_/ |_/_____/_/   /_____/_____/\\____/ /_/     \\____/_____/_/ |_/_____/_/ |_/_/  |_/_/  \\____/_/ |_|  ")
                                                                                                     

print("Parse header files to generate deserialize functions")
print("Search path: {}".format(sys.argv))
if len(sys.argv) > 1:
    print("Parse headers from {}".format(sys.argv[1]))
    headers = []
    #process input headers
    for filePath in Path(sys.argv[1]).rglob('*.h'):
        parser = HeaderParser(filePath)
        parser.processHeader()
        headers.append(parser)
        parser.stats()

    #generate output headers
    for generator in headers:
        generator.generateHeader()
else:
    print("Missing path argument")