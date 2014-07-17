#!/usr/bin/env python

"""
Copyright 2014 Matthew Borger <matthew@borgernet.com>

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
"""

## @brief A class to give meaning to common data types.
#
# Often data types are shared for multiple purposes such as using longs
# to represent ids for an object model. It can get confusing to be passing
# around longs that might not represent an id for the model you're working with.
# You can create a new type ModelId which extends a TypeWrapper<long> to
# have more type safety over working with primitives.
# The constructor can also be overriden to provide some validation.
# The stored value is designed to be immutable.
class TypeWrapper:
    def __init__(self, value):
        self.value = value

    ##
    # The class name is checked to prevent two different subclasses
    # of TypeWrapper from being considered equivalent even if their
    # stored values are equivalent.
    def __eq__(self, other):
        return (self.__class__==other.__class__) and (self.value==other.value)

    def __hash__(self):
        return self.value.__hash__()

    def __str__(self):
        return "{0}: {1}".format(self.__class__.__name__, self.value.__str__())

    def getValue(self):
        return self.value
