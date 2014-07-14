/*
 * Copyright 2014 Matthew Borger <matthew@borgernet.com>
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 * http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include <functional>

/**
 * @brief Pointer comparator
 *
 * This is a comparator function that works with containers of pointers.
 * It wraps any of the standard comparators and applies their comparison
 * logic to dereferenced objects.
 *
 * @tparam Type
 * 		The object to compare.
 * @tparam Compare
 * 		The non-pointer comparator to use.
 * 		Defaults to std::less.
 */
template<typename Type, typename Compare = std::less<Type> >
struct pComp : public std::binary_function<Type *, Type *, bool> {
    bool operator()(const Type *x, const Type *y) const
        { return Compare()(*x, *y); }
};
