from TypeWrapper import TypeWrapper

class DogId(TypeWrapper):
    class InvalidDogId(Exception):
        def __init__(self):
            Exception.__init__(self, "Invalid DogId")

    def __init__(self, value):
        if( value % 2 != 0):
                raise self.InvalidDogId()
        self.value = value

tw = TypeWrapper(4)
di1 = DogId(4)
di2 = DogId(8)
di3 = DogId(4)

print("tw  = {}".format(tw))
print("di1 = {}".format(di1))
print("di2 = {}".format(di2))
print("di3 = {}".format(di3))

print("tw  == di1\t{}".format(tw == di1))
print("di1 == di2\t{}".format(di1 == di2))
print("di1 == di3\t{}".format(di1 == di3))

print("DogId(5) is invalid!")
di4 = DogId(5)
