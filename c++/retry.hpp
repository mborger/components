/*
 * Copyright 2015 Matthew Borger <matthew@borgernet.com>
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

#include <exception>
#include <random>
#include <thread>

namespace std {

/**
 * @brief Standard retrying function
 *
 * This function will handle retrying execution
 * for a specified number of times and provide
 * a randomized increasing sleep period that will
 * last no longer than the specified maximum.
 *
 * Example usage:
 * @code
 * std::retry( [](){
 * 	someUnreliableFunction();
 * 	}, 3, 100);
 * @endcode
 *
 * @tparam functor Anything that implements operator() including lambdas
 * @param maxAttempts The maximum number of attempts to execute functor
 * @param maxSleepMilliseconds The maximum period to sleep between executions
 */
template<typename FUNCTOR>
void
retry(FUNCTOR functor, int maxAttempts, int maxSleepMilliseconds)
{
	float attempt = 1;
	std::exception functorException;
	std::random_device rd;
	std::minstd_rand gen(rd());
	int lowerBound = 0;
	do {
		try {
			functor();
			return;
		} catch(std::exception const& e) {
			functorException = e;
		}
		int upperBound = (attempt/maxAttempts) * maxSleepMilliseconds;
		std::uniform_int_distribution<> randDistribution(lowerBound, upperBound);
		lowerBound = upperBound;
		std::this_thread::sleep_for(std::chrono::milliseconds(randDistribution(gen)));
		attempt++;
	} while(attempt <= maxAttempts);
	// If execution got here there were problems
	// even after all attempts. Throw the last
	// exception.
	throw functorException;
}

} //namespace std
