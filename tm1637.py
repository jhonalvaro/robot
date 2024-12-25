from machine import Pin
import time

# Constants
BIT_TIME = 100  # Bit time in us, note TM1637 max data rate of 500kHz assuming short signal path

# Define library scope constants
tm1637ByteSetData = 0x40  # 0x40 [01000000] = Indicate command to display data
tm1637ByteSetAddr = 0xC0  # 0xC0 [11000000] = Start address write out all display bytes
tm1637ByteSetOn = 0x88    # 0x88 [10001000] = Display ON, plus brightness
tm1637ByteSetOff = 0x80   # 0x80 [10000000] = Display OFF
# Used to output the segment data for numbers 0..9
tm1637DisplayNumtoSeg = [0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f]

# Define the library scope variables
portTris = None
portLatch = None
portPins = None
tm1637dioTrisBit = 0
tm1637clkTrisBit = 0
tm1637MaxDigits = 0
tm1637RightDigit = 0
tm1637Brightness = 0
tm1637Data = [1, 2, 3, 4, 5, 6]
decimalPointPos = 0
ldgZeroBlanking = 0
reorderDigits = 0

def tm1637initialise(tris, portPins, portLatch, dataBit, clkBit, displayType, brightness):
    global portTris, portLatch, portPins, tm1637dioTrisBit, tm1637clkTrisBit, tm1637MaxDigits, tm1637RightDigit, tm1637Brightness, reorderDigits
    portLatch = portLatch
    portPins = portPins
    portTris = tris
    if displayType == 1:
        tm1637MaxDigits = 4
    elif displayType == 6:
        tm1637MaxDigits = 6
    elif displayType == 7:
        tm1637MaxDigits = 6
        reorderDigits = 1
    tm1637RightDigit = tm1637MaxDigits - 1
    tm1637dioTrisBit = dataBit
    tm1637clkTrisBit = clkBit
    tm1637Brightness = brightness
    portLatch.value(portLatch.value() & ~(1 << dataBit))
    portLatch.value(portLatch.value() & ~(1 << clkBit))
    portTris.value(portTris.value() | (1 << dataBit))
    portTris.value(portTris.value() | (1 << clkBit))

def tm1637output(outputInteger, decimalPos, round, ldgZeroBlank, rightShift):
    global ldgZeroBlanking, decimalPointPos
    ldgZeroBlanking = ldgZeroBlank
    decimalPointPos = decimalPos
    getDigits(outputInteger)
    if round:
        roundDigits(round)
    if rightShift:
        rightShiftDigits(rightShift)
    tm1637UpdateDisplay()

def tm1637UpdateDisplay():
    global tm1637Data, tm1637MaxDigits, tm1637RightDigit, decimalPointPos, ldgZeroBlanking, reorderDigits
    tm1637Output = [0] * 6
    tm1637DigitSegs = 0
    stopBlanking = not ldgZeroBlanking
    for ctr in range(tm1637MaxDigits):
        tm1637DigitSegs = tm1637DisplayNumtoSeg[tm1637Data[ctr]]
        if not stopBlanking and tm1637Data[ctr] == 0:
            if ctr < tm1637RightDigit:
                tm1637DigitSegs = 0
        else:
            stopBlanking = True
            if ctr == decimalPointPos:
                tm1637DigitSegs |= 0b10000000
        tm1637Output[ctr] = tm1637DigitSegs
    tm1637StartCondition()
    tm1637ByteWrite(tm1637ByteSetData)
    tm1637StopCondition()
    tm1637StartCondition()
    tm1637ByteWrite(tm1637ByteSetAddr)
    if reorderDigits:
        tm1637OutputPattern = [2, 1, 0, 5, 4, 3]
        for ctr in range(tm1637MaxDigits):
            tm1637ByteWrite(tm1637Output[tm1637OutputPattern[ctr]])
    else:
        for ctr in range(tm1637MaxDigits):
            tm1637ByteWrite(tm1637Output[ctr])
    tm1637StopCondition()
    tm1637StartCondition()
    tm1637ByteWrite(tm1637ByteSetOn + tm1637Brightness)
    tm1637StopCondition()

def tm1637DisplayOn():
    tm1637StartCondition()
    tm1637ByteWrite(tm1637ByteSetOn + tm1637Brightness)
    tm1637StopCondition()

def tm1637DisplayOff():
    tm1637StartCondition()
    tm1637ByteWrite(tm1637ByteSetOff)
    tm1637StopCondition()

def tm1637StartCondition():
    portTris.value(portTris.value() & ~(1 << tm1637dioTrisBit))
    portLatch.value(portLatch.value() & ~(1 << tm1637dioTrisBit))
    time.sleep_us(BIT_TIME)

def tm1637StopCondition():
    portTris.value(portTris.value() & ~(1 << tm1637dioTrisBit))
    portLatch.value(portLatch.value() & ~(1 << tm1637dioTrisBit))
    time.sleep_us(BIT_TIME)
    portTris.value(portTris.value() | (1 << tm1637clkTrisBit))
    time.sleep_us(BIT_TIME)
    portTris.value(portTris.value() | (1 << tm1637dioTrisBit))
    time.sleep_us(BIT_TIME)

def tm1637ByteWrite(bWrite):
    for i in range(8):
        portTris.value(portTris.value() & ~(1 << tm1637clkTrisBit))
        portLatch.value(portLatch.value() & ~(1 << tm1637clkTrisBit))
        time.sleep_us(BIT_TIME)
        if bWrite & 0x01:
            portTris.value(portTris.value() | (1 << tm1637dioTrisBit))
        else:
            portTris.value(portTris.value() & ~(1 << tm1637dioTrisBit))
            portLatch.value(portLatch.value() & ~(1 << tm1637dioTrisBit))
        time.sleep_us(BIT_TIME)
        bWrite >>= 1
        portTris.value(portTris.value() | (1 << tm1637clkTrisBit))
        time.sleep_us(BIT_TIME)
    portTris.value(portTris.value() & ~(1 << tm1637clkTrisBit))
    portLatch.value(portLatch.value() & ~(1 << tm1637clkTrisBit))
    portTris.value(portTris.value() | (1 << tm1637dioTrisBit))
    portLatch.value(portLatch.value() & ~(1 << tm1637dioTrisBit))
    time.sleep_us(BIT_TIME)
    portTris.value(portTris.value() | (1 << tm1637clkTrisBit))
    time.sleep_us(BIT_TIME)
    tm1637ack = portPins.value() & (1 << tm1637dioTrisBit)
    if not tm1637ack:
        portTris.value(portTris.value() & ~(1 << tm1637dioTrisBit))
        portLatch.value(portLatch.value() & ~(1 << tm1637dioTrisBit))
    time.sleep_us(BIT_TIME)
    portTris.value(portTris.value() & ~(1 << tm1637clkTrisBit))
    portLatch.value(portLatch.value() & ~(1 << tm1637clkTrisBit))
    time.sleep_us(BIT_TIME)
    return 1

def getDigits(number):
    global tm1637Data, tm1637RightDigit, tm1637MaxDigits
    ctr = tm1637RightDigit
    for ctr2 in range(tm1637MaxDigits):
        tm1637Data[ctr2] = 0
    while number > 0:
        if ctr >= 0:
            modulus = number % 10
            tm1637Data[ctr] = modulus
            number //= 10
            ctr -= 1
        else:
            number = 0
    return 1

def roundDigits(numberToRemove):
    global tm1637Data, tm1637RightDigit
    startDigit = tm1637RightDigit
    for removeCount in range(numberToRemove):
        carry = 0
        for digit in range(startDigit, -1, -1):
            if digit == startDigit:
                if tm1637Data[digit] > 5:
                    carry = 1
                tm1637Data[digit] = 0
            if digit < startDigit:
                tm1637Data[digit] += carry
                if tm1637Data[digit] > 9:
                    tm1637Data[digit] = 0
                    carry = 1
                else:
                    carry = 0
        startDigit -= 1

def rightShiftDigits(rightShift):
    global tm1637Data, tm1637RightDigit
    if rightShift:
        for digit in range(tm1637RightDigit, -1, -1):
            shiftSource = digit - rightShift
            if shiftSource < 0:
                tm1637Data[digit] = 0
            else:
                tm1637Data[digit] = tm1637Data[shiftSource]
