/*
 * calls.h:
 *  Call lua functions by passing appropriate C++ types.
 */

#ifndef LUAWRAP_CALLS_H_
#define LUAWRAP_CALLS_H_

#include <luawrap/config.h>
#include <luawrap/luawrap.h>
#include <luawrap/luawraperror.h>

namespace luawrap {
	namespace _private {
		// Throws/aborts if false
		void luacall_return_check(bool check_result);
		void luacall_with_traceback(lua_State* L, int nargs);
	}

	/******************************************************************************
	 * START AUTOGENERATED CODE -- Here be DRAGONS. Use generate-calls.py         *
	 ******************************************************************************/

	template<typename R>
	    static inline R call(lua_State* L) {
	    _private::PopHack delayedpop(L);

	    _private::luacall_with_traceback(L, 0);
	    _private::luacall_return_check(check<R>(L, -1));
	    return get<R>(L, -1);
	}

	template<typename R, typename A1>
	    static inline R call(lua_State* L, const A1& arg1) {
	    _private::PopHack delayedpop(L);
	    push<A1>(L, arg1);

	    _private::luacall_with_traceback(L, 1);
	    _private::luacall_return_check(check<R>(L, -1));
	    return get<R>(L, -1);
	}

	template<typename R, typename A1,typename A2>
	    static inline R call(lua_State* L, const A1& arg1, const A2& arg2) {
	    _private::PopHack delayedpop(L);
	    push<A1>(L, arg1);
	    push<A2>(L, arg2);

	    _private::luacall_with_traceback(L, 2);
	    _private::luacall_return_check(check<R>(L, -1));
	    return get<R>(L, -1);
	}

	template<typename R, typename A1,typename A2,typename A3>
	    static inline R call(lua_State* L, const A1& arg1, const A2& arg2, const A3& arg3) {
	    _private::PopHack delayedpop(L);
	    push<A1>(L, arg1);
	    push<A2>(L, arg2);
	    push<A3>(L, arg3);

	    _private::luacall_with_traceback(L, 3);
	    _private::luacall_return_check(check<R>(L, -1));
	    return get<R>(L, -1);
	}

	template<typename R, typename A1,typename A2,typename A3,typename A4>
	    static inline R call(lua_State* L, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4) {
	    _private::PopHack delayedpop(L);
	    push<A1>(L, arg1);
	    push<A2>(L, arg2);
	    push<A3>(L, arg3);
	    push<A4>(L, arg4);

	    _private::luacall_with_traceback(L, 4);
	    _private::luacall_return_check(check<R>(L, -1));
	    return get<R>(L, -1);
	}

	template<typename R, typename A1,typename A2,typename A3,typename A4,typename A5>
	    static inline R call(lua_State* L, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5) {
	    _private::PopHack delayedpop(L);
	    push<A1>(L, arg1);
	    push<A2>(L, arg2);
	    push<A3>(L, arg3);
	    push<A4>(L, arg4);
	    push<A5>(L, arg5);

	    _private::luacall_with_traceback(L, 5);
	    _private::luacall_return_check(check<R>(L, -1));
	    return get<R>(L, -1);
	}

	template<typename R, typename A1,typename A2,typename A3,typename A4,typename A5,typename A6>
	    static inline R call(lua_State* L, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5, const A6& arg6) {
	    _private::PopHack delayedpop(L);
	    push<A1>(L, arg1);
	    push<A2>(L, arg2);
	    push<A3>(L, arg3);
	    push<A4>(L, arg4);
	    push<A5>(L, arg5);
	    push<A6>(L, arg6);

	    _private::luacall_with_traceback(L, 6);
	    _private::luacall_return_check(check<R>(L, -1));
	    return get<R>(L, -1);
	}

#ifdef LUAWRAP_LONG_CALLS
	template<typename R, typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7>
	    static inline R call(lua_State* L, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5, const A6& arg6, const A7& arg7) {
	    _private::PopHack delayedpop(L);
	    push<A1>(L, arg1);
	    push<A2>(L, arg2);
	    push<A3>(L, arg3);
	    push<A4>(L, arg4);
	    push<A5>(L, arg5);
	    push<A6>(L, arg6);
	    push<A7>(L, arg7);

	    _private::luacall_with_traceback(L, 7);
	    _private::luacall_return_check(check<R>(L, -1));
	    return get<R>(L, -1);
	}

	template<typename R, typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8>
	    static inline R call(lua_State* L, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5, const A6& arg6, const A7& arg7, const A8& arg8) {
	    _private::PopHack delayedpop(L);
	    push<A1>(L, arg1);
	    push<A2>(L, arg2);
	    push<A3>(L, arg3);
	    push<A4>(L, arg4);
	    push<A5>(L, arg5);
	    push<A6>(L, arg6);
	    push<A7>(L, arg7);
	    push<A8>(L, arg8);

	    _private::luacall_with_traceback(L, 8);
	    _private::luacall_return_check(check<R>(L, -1));
	    return get<R>(L, -1);
	}

	template<typename R, typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9>
	    static inline R call(lua_State* L, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5, const A6& arg6, const A7& arg7, const A8& arg8, const A9& arg9) {
	    _private::PopHack delayedpop(L);
	    push<A1>(L, arg1);
	    push<A2>(L, arg2);
	    push<A3>(L, arg3);
	    push<A4>(L, arg4);
	    push<A5>(L, arg5);
	    push<A6>(L, arg6);
	    push<A7>(L, arg7);
	    push<A8>(L, arg8);
	    push<A9>(L, arg9);

	    _private::luacall_with_traceback(L, 9);
	    _private::luacall_return_check(check<R>(L, -1));
	    return get<R>(L, -1);
	}

	template<typename R, typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9,typename A10>
	    static inline R call(lua_State* L, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5, const A6& arg6, const A7& arg7, const A8& arg8, const A9& arg9, const A10& arg10) {
	    _private::PopHack delayedpop(L);
	    push<A1>(L, arg1);
	    push<A2>(L, arg2);
	    push<A3>(L, arg3);
	    push<A4>(L, arg4);
	    push<A5>(L, arg5);
	    push<A6>(L, arg6);
	    push<A7>(L, arg7);
	    push<A8>(L, arg8);
	    push<A9>(L, arg9);
	    push<A10>(L, arg10);

	    _private::luacall_with_traceback(L, 10);
	    _private::luacall_return_check(check<R>(L, -1));
	    return get<R>(L, -1);
	}

	template<typename R, typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9,typename A10,typename A11>
	    static inline R call(lua_State* L, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5, const A6& arg6, const A7& arg7, const A8& arg8, const A9& arg9, const A10& arg10, const A11& arg11) {
	    _private::PopHack delayedpop(L);
	    push<A1>(L, arg1);
	    push<A2>(L, arg2);
	    push<A3>(L, arg3);
	    push<A4>(L, arg4);
	    push<A5>(L, arg5);
	    push<A6>(L, arg6);
	    push<A7>(L, arg7);
	    push<A8>(L, arg8);
	    push<A9>(L, arg9);
	    push<A10>(L, arg10);
	    push<A11>(L, arg11);

	    _private::luacall_with_traceback(L, 11);
	    _private::luacall_return_check(check<R>(L, -1));
	    return get<R>(L, -1);
	}

	template<typename R, typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9,typename A10,typename A11,typename A12>
	    static inline R call(lua_State* L, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5, const A6& arg6, const A7& arg7, const A8& arg8, const A9& arg9, const A10& arg10, const A11& arg11, const A12& arg12) {
	    _private::PopHack delayedpop(L);
	    push<A1>(L, arg1);
	    push<A2>(L, arg2);
	    push<A3>(L, arg3);
	    push<A4>(L, arg4);
	    push<A5>(L, arg5);
	    push<A6>(L, arg6);
	    push<A7>(L, arg7);
	    push<A8>(L, arg8);
	    push<A9>(L, arg9);
	    push<A10>(L, arg10);
	    push<A11>(L, arg11);
	    push<A12>(L, arg12);

	    _private::luacall_with_traceback(L, 12);
	    _private::luacall_return_check(check<R>(L, -1));
	    return get<R>(L, -1);
	}

	template<typename R, typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9,typename A10,typename A11,typename A12,typename A13>
	    static inline R call(lua_State* L, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5, const A6& arg6, const A7& arg7, const A8& arg8, const A9& arg9, const A10& arg10, const A11& arg11, const A12& arg12, const A13& arg13) {
	    _private::PopHack delayedpop(L);
	    push<A1>(L, arg1);
	    push<A2>(L, arg2);
	    push<A3>(L, arg3);
	    push<A4>(L, arg4);
	    push<A5>(L, arg5);
	    push<A6>(L, arg6);
	    push<A7>(L, arg7);
	    push<A8>(L, arg8);
	    push<A9>(L, arg9);
	    push<A10>(L, arg10);
	    push<A11>(L, arg11);
	    push<A12>(L, arg12);
	    push<A13>(L, arg13);

	    _private::luacall_with_traceback(L, 13);
	    _private::luacall_return_check(check<R>(L, -1));
	    return get<R>(L, -1);
	}

	template<typename R, typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9,typename A10,typename A11,typename A12,typename A13,typename A14>
	    static inline R call(lua_State* L, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5, const A6& arg6, const A7& arg7, const A8& arg8, const A9& arg9, const A10& arg10, const A11& arg11, const A12& arg12, const A13& arg13, const A14& arg14) {
	    _private::PopHack delayedpop(L);
	    push<A1>(L, arg1);
	    push<A2>(L, arg2);
	    push<A3>(L, arg3);
	    push<A4>(L, arg4);
	    push<A5>(L, arg5);
	    push<A6>(L, arg6);
	    push<A7>(L, arg7);
	    push<A8>(L, arg8);
	    push<A9>(L, arg9);
	    push<A10>(L, arg10);
	    push<A11>(L, arg11);
	    push<A12>(L, arg12);
	    push<A13>(L, arg13);
	    push<A14>(L, arg14);

	    _private::luacall_with_traceback(L, 14);
	    _private::luacall_return_check(check<R>(L, -1));
	    return get<R>(L, -1);
	}

	template<typename R, typename A1,typename A2,typename A3,typename A4,typename A5,typename A6,typename A7,typename A8,typename A9,typename A10,typename A11,typename A12,typename A13,typename A14,typename A15>
	    static inline R call(lua_State* L, const A1& arg1, const A2& arg2, const A3& arg3, const A4& arg4, const A5& arg5, const A6& arg6, const A7& arg7, const A8& arg8, const A9& arg9, const A10& arg10, const A11& arg11, const A12& arg12, const A13& arg13, const A14& arg14, const A15& arg15) {
	    _private::PopHack delayedpop(L);
	    push<A1>(L, arg1);
	    push<A2>(L, arg2);
	    push<A3>(L, arg3);
	    push<A4>(L, arg4);
	    push<A5>(L, arg5);
	    push<A6>(L, arg6);
	    push<A7>(L, arg7);
	    push<A8>(L, arg8);
	    push<A9>(L, arg9);
	    push<A10>(L, arg10);
	    push<A11>(L, arg11);
	    push<A12>(L, arg12);
	    push<A13>(L, arg13);
	    push<A14>(L, arg14);
	    push<A15>(L, arg15);

	    _private::luacall_with_traceback(L, 15);
	    _private::luacall_return_check(check<R>(L, -1));
	    return get<R>(L, -1);
	}
#endif /*LUAWRAP_LONG_CALLS*/

	/******************************************************************************
	 * END AUTOGENERATED CODE -- Here be DRAGONS. Use generate-calls.py           *
	 ******************************************************************************/
}

#endif /* LUAWRAP_CALLS_H_*/
