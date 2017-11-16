from Instruction import Instruction
import re

jumpInstructions    = ["J","BEQ","BNE","HLT"] 
zeroExInstructions  = ["J","BEQ","BNE","LI"]
oneExInstructions   = ["AND","ANDI","OR","ORI","LW","SW"]
twoExInstructions   = ["ADD","ADDI","SUB","SUBI"]
threeExInstructions = ["MULT","MULTI"]

allInstructions = zeroExInstructions + oneExInstructions + twoExInstructions + threeExInstructions

def Fetch(pipeline,publishList,rawIndex,line):
    if pipeline["stallBeforeFetch"] == 0:
        pipeline["instStallBool"] = 0
        newInstruction = Instruction(line, rawIndex,len(publishList))
        publishList.append([line.replace("\n",""), " "," "," "," "," "])
        pipeline["Fetch"] = [newInstruction,0]
        rawIndex += 1
        pipeline["iAccessRequests"] += 1
    else:
        pipeline["stallBeforeFetch"] -= 1

    return rawIndex    

def Decode(pipeline,cycle,publishList,registers):
    if not pipeline["Fetch"][0] == None:
        if pipeline["Fetch"][1] == 0:
            aOK = True            
            if pipeline["Fetch"][0].name in zeroExInstructions:
                for reg in pipeline["Fetch"][0].registersNeeded:
                    if reg in registers["inUse"]:
                        aOK = False
            if aOK:
                publishList[pipeline["Fetch"][0].publishID][1] = cycle
                pipeline["Decode"] = pipeline["Fetch"]
                pipeline["Fetch"] = [None,0]
            else:
                #data hazard stall 
                pipeline["Decode"] = [None,0]
                pipeline["Fetch"][1] += 1
                #two becoause, it's about to get decremented
                pipeline["stallBeforeFetch"] += 2
                
        else:
            pipeline["Fetch"][1] -= 1

    else:

        if pipeline["Fetch"][1] > 0:
            pipeline["Fetch"][1] -=1
        elif not pipeline["dataStallBool"]:
            pipeline["Decode"] = pipeline["Fetch"]
            pipeline["Fetch"] = [None,0]

        elif pipeline["stallBeforeFetch"] > 0:
            pipeline["Decode"] = [None,0]



def Execution1(pipeline,cycle,publishList,dataCacheList,registers,memory,
               labels,rawIndex):
    #do the Decode stuff

    if not pipeline["Decode"][0] == None:
        aOK = True
        for reg in pipeline["Decode"][0].registersNeeded:
            if reg in registers["inUse"]:
                aOK = False

        if pipeline["Decode"][1] == 0 and aOK:
            #check if registers available
            publishList[pipeline["Decode"][0].publishID][2] = cycle
            pipeline["Execution1"] = pipeline["Decode"]
            if pipeline["Execution1"][0].name in zeroExInstructions:
                pipeline["Execution1"][0].execute(registers,memory,dataCacheList)

            if pipeline["Execution1"][0].arg1:
                if pipeline["Execution1"][0].name in oneExInstructions or pipeline["Execution1"][0].name in twoExInstructions or pipeline["Execution1"][0].name in threeExInstructions:
                    registers["inUse"].append(pipeline["Execution1"][0].arg1)
                elif pipeline["Execution1"][0].name in jumpInstructions:
                    #
                    # JUMPING
                    #
                    dicks = pipeline["Execution1"][0].jump(rawIndex,labels,registers)
                    print "\n\nJUMPING\n\n"
                    print "newLocation:",dicks
                    print "rawIndex:",rawIndex
                    print "\n\n"
                    publishList[pipeline["Fetch"][0].publishID][1] = cycle
                    pipeline["Fetch"] = [None,0]

                    if not dicks == rawIndex:
                        if rawIndex > dicks:
                            pipeline["stallBeforeFetch"] += rawIndex - dicks

                    return dicks
        else:
            if not pipeline["dataStallBool"]:
                print "DATA HAZARD STALL"
                pipeline["Execution1"]        = [None,pipeline["Execution2"][1]]
                #data hazard stall
                pipeline["Decode"][1]        += 1
                pipeline["Fetch"][1]         += 1
                pipeline["stallBeforeFetch"] += 1
            else:
                if not aOK:
                    pipeline["Decode"][1] += 1
                    pipeline["Fetch"][1] += 1
                    pipeline["stallBeforeFetch"] += 1
                    #
                    #Experimental portion <<<<<<<

                    pipeline["Execution1"] = [None,0]
                    # ^^^^^^^^^^^^^^^^^^^^^^^^^^^^


        if pipeline["Decode"][1] > 0:
            pipeline["Decode"][1] -= 1

    else:
        if cycle == 99:
            print "YOOOOOO"
            print pipeline["Execution1"]
        if pipeline["Decode"][1] > 0:
            pipeline["Decode"][1] -= 1
            return rawIndex
        elif pipeline["Execution1"][1] > 0:
            pipeline["Decode"][1] = pipeline["Execution1"][1]
            
        pipeline["Execution1"] = pipeline["Decode"]
    if cycle == 99:
        print "BOT of EX1 CALL"
        print "Ex1:",pipeline["Execution1"]

    return rawIndex

def Execution2(pipeline,cycle,publishList,dataCacheList,registers,memory):
    #do the Execution1 stuff
    if not pipeline["Execution1"][0] == None:
        print pipeline["Execution1"][0]
        if pipeline["Execution1"][1] == 0:
            pipeline["Execution2"] = pipeline["Execution1"]
            if pipeline["Execution2"][0].name in oneExInstructions:
                #EXPERIMENTALvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
                pipeline["dataStall"] += pipeline["Execution1"][0].execute(registers,memory,dataCacheList)
                #^^^^^^^^^^^^^^^^^^^^^^^^^^^the plus part
                if pipeline["dataStall"] > 0:
                    pipeline["dataStallBool"] = 3

                if pipeline["dataStallBool"] == False:
                    if not pipeline["Execution2"][0].name == "SW":
                        registers["inUse"].remove(pipeline["Execution2"][0].arg1)
                else:
                    if not pipeline["Execution2"][0].name.endswith("W"):
                        registers["inUse"].remove(pipeline["Execution2"][0].arg1)
        else:
            pipeline["Execution1"][1] -= 1
            if pipeline["dataStallBool"] == False:
                pipeline["Execution2"] == [None,0]

    else:
        if pipeline["Execution1"][1] > 0:
            pipeline["Execution1"][1] -= 1
        elif pipeline["Execution2"][1] > 0 and pipeline["Execution3"][1] > 0 and pipeline["Execution2"][1] == pipeline["Execution3"][1]:
            pipeline["Execution1"][1] = pipeline["Execution2"][1]
        elif pipeline["Fetch"][1] > 0:
            #MAYBE??????????
            pipeline["Execution1"][1] = pipeline["Fetch"][1]
        else:
            pipeline["Execution2"] = pipeline["Execution1"]
        #possibly add an elif case for when the thing in memory stage is LW,orSW

    if cycle==999:
        print "BOT OF EX2 CALL"
        print "(ex2):",pipeline["Execution2"]
        print "(ex1):",pipeline["Execution1"]


def Execution3(pipeline,cycle,publishList,dataCacheList,registers,memory):
    if not pipeline["Execution2"][0] == None:
        if pipeline["Execution2"][1] == 0:
            pipeline["Execution3"] = pipeline["Execution2"]
            if pipeline["Execution3"][0].name == "HLT":
                pipeline["Execution2"] = [None,0]
                pipeline["Execution1"] = [None,0]
                pipeline["Decode"] = [None,0]
                pipeline["Fetch"] = [None,0]

            if pipeline["Execution3"][0].name in twoExInstructions:
                registers["inUse"].remove(pipeline["Execution3"][0].arg1)
                pipeline["Execution3"][0].execute(registers,memory,dataCacheList)
        else:
            pipeline["Execution2"][1] -= 1
            if pipeline["dataStallBool"] == False:
                pipeline["Execution3"] = [None,0]
    else:
        pipeline["Execution3"] = pipeline["Execution2"]

def Memory(pipeline,cycle,publishList,dataCacheList,registers,memory):
    if not pipeline["Execution3"][0] == None:
        if pipeline["Execution3"][1] == 0:
            if pipeline["Execution3"][0].name not in jumpInstructions:
                publishList[pipeline["Execution3"][0].publishID][3] = cycle
            pipeline["Memory"] = pipeline["Execution3"]

            if pipeline["Memory"][0].name in threeExInstructions:
                registers["inUse"].remove(pipeline["Memory"][0].arg1)
                pipeline["Memory"][0].execute(registers,memory,dataCacheList)
        else:
            pipeline["Execution3"][1] -=1
            if pipeline["dataStallBool"] == False:
                pipeline["Memory"] = [None,0]
    else:
        if not pipeline["dataStallBool"]:
            pipeline["Memory"] = pipeline["Execution3"]

def WriteBack(pipeline,cycle,publishList,dataCacheList,registers):
    if not pipeline["Memory"][0] == None:
        if pipeline["dataStall"] and pipeline["Memory"][0].name == "LW":
            stallCycles = 12 + pipeline["stallBeforeFetch"]
            pipeline["Memory"][1]        += stallCycles
            pipeline["Execution3"][1]    += stallCycles
            pipeline["Execution2"][1]    += stallCycles
            pipeline["Execution1"][1]    += stallCycles
            pipeline["Decode"][1]        += stallCycles
            pipeline["Fetch"][1]         += 12
            pipeline["stallBeforeFetch"] += 1
            pipeline["dataStall"]         = 0
            pipeline["dataStallBool"]     = True

        if pipeline["Memory"][1] == 0:
            if pipeline["Memory"][0].name not in jumpInstructions:
                publishList[pipeline["Memory"][0].publishID][4] = cycle
            pipeline["WriteBack"] = pipeline["Memory"]
            if pipeline["WriteBack"][0].name.endswith("W"):
                if pipeline["dataStallBool"]:
                    registers["inUse"].remove(pipeline["WriteBack"][0].arg1)
                    pipeline["dataStallBool"] = False
                    pipeline["Fetch"][1] = 0
                    pipeline["Decode"][1] = 0
                else:
                    if pipeline["WriteBack"][0].name == "SW" or pipeline["WriteBack"][0].name == "LW":
                        if pipeline["WriteBack"][0].arg1 in registers["inUse"]:
                            registers["inUse"].remove(pipeline["WriteBack"][0].arg1)
                    else:
                        registers["inUse"].remove(pipeline["WriteBack"][0].arg1)
    
            
        else:
            pipeline["Memory"][1] -= 1
            pipeline["WriteBack"] = [None,0]
    else:
        pipeline["WriteBack"] = pipeline["Memory"]
