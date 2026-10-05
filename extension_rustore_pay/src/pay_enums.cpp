#include "pay_enums.h"
#include "pay_enums_defs.h"

static int ReadonlyNewIndex(lua_State* L)
{
	return luaL_error(L, "Attempt to modify readonly enum table");
}

static void MakeReadonly(lua_State* L, int index)
{
	if (index < 0) index = lua_gettop(L) + index + 1;

	lua_newtable(L);                         // mt
	lua_pushcfunction(L, ReadonlyNewIndex);  // mt.__newindex
	lua_setfield(L, -2, "__newindex");

	lua_pushboolean(L, 0);                   // mt.__metatable = false
	lua_setfield(L, -2, "__metatable");

	lua_setmetatable(L, index);
}

static inline void PushKV(lua_State* L, const char* k, const char* v)
{
	lua_pushstring(L, v);
	lua_setfield(L, -2, k);
}

static void PushEnumTable(lua_State* L, void (*fill)(lua_State*))
{
	lua_newtable(L);
	fill(L);
	MakeReadonly(L, -1);
}

// ---- fill functions (используют списки из pay_enums_defs.h)

static void FillPurchaseType(lua_State* L)
{
	#define X(KEY, VAL) PushKV(L, #KEY, VAL);
	PAY_ENUM_PURCHASE_TYPE(X)
	#undef X
}

static void FillPreferredPurchaseType(lua_State* L)
{
	#define X(KEY, VAL) PushKV(L, #KEY, VAL);
	PAY_ENUM_PREFERRED_PURCHASE_TYPE(X)
	#undef X
}

static void FillUserAuthorizationStatus(lua_State* L)
{
	#define X(KEY, VAL) PushKV(L, #KEY, VAL);
	PAY_ENUM_USER_AUTH_STATUS(X)
	#undef X
}

static void FillProductType(lua_State* L)
{
	#define X(KEY, VAL) PushKV(L, #KEY, VAL);
	PAY_ENUM_PRODUCT_TYPE(X)
	#undef X
}

static void FillApplicationPurchaseStatus(lua_State* L)
{
	#define X(KEY, VAL) PushKV(L, #KEY, VAL);
	PAY_ENUM_APPLICATION_PURCHASE_STATUS(X)
	#undef X
}

static void FillProductPurchaseStatus(lua_State* L)
{
	#define X(KEY, VAL) PushKV(L, #KEY, VAL);
	PAY_ENUM_PRODUCT_PURCHASE_STATUS(X)
	#undef X
}

static void FillSubscriptionPurchaseStatus(lua_State* L)
{
	#define X(KEY, VAL) PushKV(L, #KEY, VAL);
	PAY_ENUM_SUBSCRIPTION_PURCHASE_STATUS(X)
	#undef X
}

static void FillSdkTheme(lua_State* L)
{
	#define X(KEY, VAL) PushKV(L, #KEY, VAL);
	PAY_ENUM_SDK_THEME(X)
	#undef X
}

static void FillAcknowledgementState(lua_State* L)
{
	#define X(KEY, VAL) PushKV(L, #KEY, VAL);
	PAY_ENUM_ACKNOWLEDGEMENT_STATE(X)
	#undef X
}

// ---- public API

void RegisterGlobalRuStorePayEnums(lua_State* L)
{
	int top = lua_gettop(L);

	lua_newtable(L); // root

	PushEnumTable(L, FillPurchaseType);
	lua_setfield(L, -2, "PurchaseType");

	PushEnumTable(L, FillPreferredPurchaseType);
	lua_setfield(L, -2, "PreferredPurchaseType");

	PushEnumTable(L, FillUserAuthorizationStatus);
	lua_setfield(L, -2, "UserAuthorizationStatus");

	PushEnumTable(L, FillProductType);
	lua_setfield(L, -2, "ProductType");

	PushEnumTable(L, FillApplicationPurchaseStatus);
	lua_setfield(L, -2, "ApplicationPurchaseStatus");

	PushEnumTable(L, FillProductPurchaseStatus);
	lua_setfield(L, -2, "ProductPurchaseStatus");

	PushEnumTable(L, FillSubscriptionPurchaseStatus);
	lua_setfield(L, -2, "SubscriptionPurchaseStatus");

	PushEnumTable(L, FillSdkTheme);
	lua_setfield(L, -2, "SdkTheme");

	PushEnumTable(L, FillAcknowledgementState);
	lua_setfield(L, -2, "AcknowledgementState");

	MakeReadonly(L, -1);

	lua_setglobal(L, "RuStorePayEnums");

	assert(top == lua_gettop(L));
}
