import re
class Instruction:

    def __init__(self, line, rawID, publishID):
        self.arg1 = None
        self.arg2 = None
        self.arg3 = None
        self.registersNeeded = []
        lineList = line.split()
        
        self.rawID = rawID
        self.publishID = publishID
        if lineList[0].endswith(":"):
            lineList = lineList[1:]
        self.name = lineList[0].upper()
        if len(lineList) > 1:
            argList = lineList[1].split(",")
            self.arg1 = argList[0]
            if len(argList) > 1:
                registerPattern = re.compile("(R\d+)")
                self.arg2 = argList[1]
                self.registersNeeded += registerPattern.findall(argList[1])
                if self.name.startswith("B"):
                    self.registersNeeded.append(self.arg1)
                if len(argList) >  2:
                    self.arg3 = argList[2]
                    self.registersNeeded += registerPattern.findall(self.arg3)

        print self.name,self.arg1
                    

    def execute(self, registers,memory,dataCacheList):
        #zero execution cycles
        if self.name == "LI":
            if self.arg2.endswith("h"):
                self.arg2 = int(self.arg2[:-1], 16)
            registers[self.arg1] = int(self.arg2)
            
        
        elif self.name == "ANDI":
            #ONE CYCLE INSTRUCTIONS
            registers[self.arg1] = int(registers[self.arg2]) & int(self.arg3)
        elif self.name == "AND":
            registers[self.arg1] = int(registers[self.arg2]) & int(registers[self.arg3])
        elif self.name == "ORI":
            registers[self.arg1] = int(registers[self.arg2]) | int(self.arg3)

        elif self.name == "OR":
            print registers
            registers[self.arg1] = int(registers[self.arg2]) | int(registers[self.arg3])

        elif self.name == "LW":
            registers["dAccessRequests"] += 1
            # parse out the memAddress
            shit = self.arg2
            shit = shit.split("(")
            offset = shit[0]
            register = shit[1].replace(")","")
            address = int(offset) + int(registers[register])
            memIndex = (address % 256) / 4
            # check if desired thing is in the cache, return stall (0, or 12)
            if memIndex in dataCacheList:
                #data cache hit
                registers["dCacheHits"] += 1
                registers[self.arg1] = memory[memIndex]
            else:
                #data cache miss
                blockIndex = (memIndex % 16) /4
                for i in range(4):
                    word = (memIndex + i) % 4 + blockIndex * 4
                    dataCacheList[(blockIndex*4) + (memIndex + i)%4] = word
                registers[self.arg1] = memory[memIndex]
                return 3

        elif self.name == "SW":
            registers["dAccessRequests"] += 1
            shit = self.arg2
            shit = shit.split("(")
            offset = int(shit[0])
            register = shit[1].replace(")","")
            address = offset + int(registers[register])
            memIndex = (address % 256) / 4
            # not sure about htis
            if memIndex in dataCacheList:
                registers["dCacheHits"] += 1
                shit = self.arg2
                shit = shit.split("(")
                offset = int(shit[0])
                register = shit[1].replace(")","")
                #address = offset + int(registers[register])                
                memory[memIndex] = offset + int(registers[register])
            else:
                blockIndex = (memIndex % 16) /4
                for i in range(4):
                    word = (memIndex + i) % 4 + blockIndex * 4
                    dataCacheList[(blockIndex*4) + (memIndex + i)%4] = word
                registers[self.arg1] = memory[memIndex]
                return 3
                


        elif self.name == "ADDI":
            # TWO CYCLE INSTRUCTIONS
            if self.arg3.endswith("h"):
                self.arg3 = int(self.arg3[:-1], 16)
            registers[self.arg1] = int(registers[self.arg2]) + int(self.arg3)
        elif self.name == "ADD":
            registers[self.arg1] = int(registers[self.arg2]) + int(registers[self.arg3])
        elif self.name == "SUBI":
            registers[self.arg1] = int(registers[self.arg2]) - int(self.arg3)
        elif self.name == "SUB":
            registers[self.arg1] = int(registers[self.arg2]) - int(registers[self.arg3])

        elif self.name == "MULTI":
            registers[self.arg1] = int(registers[self.arg2]) * int(self.arg3)
        elif self.name == "MULT":
            registers[self.arg1] = int(registers[self.arg2]) * int(registers[self.arg3])
        else:
            print "Did thing"
        return 0

    def jump(self,rawIndex,labels,registers):
        if self.name == "J":
            rawIndex = labels[self.arg1]
            #print rawIndex
        elif self.name == "BNE":
            if not int(registers[self.arg1]) == int(registers[self.arg2]):
                rawIndex = labels[self.arg3]
                
        elif self.name == "BEQ":
            if int(registers[self.arg1]) == int(registers[self.arg2]):
                rawIndex = labels[self.arg3]
        return rawIndex


    def printMe(self):
        print self.name, self.arg1, self.arg2, self.arg3

