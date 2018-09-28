// sol3

// The MIT License (MIT)

// Copyright (c) 2013-2018 Rapptz, ThePhD and contributors

// Permission is hereby granted, free of charge, to any person obtaining a copy of
// this software and associated documentation files (the "Software"), to deal in
// the Software without restriction, including without limitation the rights to
// use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
// the Software, and to permit persons to whom the Software is furnished to do so,
// subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
// FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
// IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
// CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef SOL_TABLE_HPP
#define SOL_TABLE_HPP

#include "table_core.hpp"
#include "usertype.hpp"

namespace sol {
	typedef table_core<false> table;

	template <bool top_level, typename base_type>
	template <typename Class, typename Key>
	usertype<Class> basic_table_core<top_level, base_type>::new_usertype(Key&& key, optional<no_construction> no_default_constructor /* = nullopt*/) {
		int mt_index = u_detail::register_usertype<Class>(this->lua_state(), std::move(no_default_constructor));
		usertype<Class> mt(this->lua_state(), -mt_index);
		set(std::forward<Key>(key), mt);
		return mt;
	}

	namespace stack {
		template <>
		struct getter<metatable_t> {
			static table get(lua_State* L, int index = -1) {
				if (lua_getmetatable(L, index) == 0) {
					return table(L, ref_index(LUA_REFNIL));
				}
				return table(L, -1);
			}
		};
	} // namespace stack
} // namespace sol

#endif // SOL_TABLE_HPP
