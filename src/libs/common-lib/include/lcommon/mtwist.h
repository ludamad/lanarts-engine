/*
 Modified mtwist class, original license follows.

 A C-program for MT19937, with initialization improved 2002/1/26.
 Coded by Takuji Nishimura and Makoto Matsumoto.

 Before using, initialize the state by using init_genrand(seed)
 or init_by_array(init_key, key_length).

 Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions
 are met:

 1. Redistributions of source code must retain the above copyright
 notice, this list of conditions and the following disclaimer.

 2. Redistributions in binary form must reproduce the above copyright
 notice, this list of conditions and the following disclaimer in the
 documentation and/or other materials provided with the distribution.

 3. The names of its contributors may not be used to endorse or promote
 products derived from this software without specific prior written
 permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


 Any feedback is very welcome.
 http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
 email: m-mat @ math.sci.hiroshima-u.ac.jp (remove space)
 */

#ifndef LCOMMON_MTWIST_H_
#define LCOMMON_MTWIST_H_

#include "Range.h"

class MTwist {
public:

	void init_genrand(unsigned int s);
	void init_by_array(unsigned int init_key[], int key_length);

	MTwist() :
			mti(N + 1) {
		_amount_generated = 0;
	}

	MTwist(unsigned int s) :
			mti(N + 1) {
		_amount_generated = 0;
		init_genrand(s);
	}
	MTwist(unsigned int init_key[], int key_length) :
			mti(N + 1) {
		_amount_generated = 0;
		init_by_array(init_key, key_length);
	}

	int rand() {
		_amount_generated++;
		return genrand_int32();
	}
	int rand(int max) {
		if (max == 1)
			return 0;
		_amount_generated++;
		return genrand_int32() % max;
	}
	int rand(int min, int max) {
		return rand(max - min) + min;
	}

	int rand(const Range& r) {
		return rand(r.min, r.max + 1);
	}
	double randf() {
		_amount_generated++;
		return genrand_real1();
	}
	float rand(const RangeF& r) {
		_amount_generated++;
		return float((r.max - r.min) * genrand_real1() + r.min);
	}

	double guassian(double average, double std_dev, int n_trials);

	int amount_generated() const {
		return _amount_generated;
	}

private:
	enum {
		N = 624
	};
	unsigned int mt[N];
	int mti;

	int _amount_generated;

	/* generates a random number on [0,0xffffffff]-interval */
	unsigned int genrand_int32(void);

	/* generates a random number on [0,0x7fffffff]-interval */
	int genrand_int31(void);

	/* generates a random number on [0,1]-real-interval */
	double genrand_real1(void);

	/* generates a random number on [0,1)-real-interval */
	double genrand_real2(void);

	/* generates a random number on (0,1)-real-interval */
	double genrand_real3(void);

	/* generates a random number on [0,1) with 53-bit resolution*/
	double genrand_res53(void);
};

#endif /* LCOMMON_MTWIST_H_ */
