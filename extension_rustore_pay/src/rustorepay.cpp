#define EXTENSION_NAME RuStorePay
#define LIB_NAME "RuStorePay"
#define MODULE_NAME "rustorepay"
#define DEBUG false

#include <dmsdk/sdk.h>
#include "pay_enums.h"

#if defined(DM_PLATFORM_ANDROID)

#include <dmsdk/dlib/android.h>
#include <string>
#include <vector>
#include "AndroidJavaObject.h"

using namespace RuStoreSDK;

static void GetJavaPayInstance(JNIEnv* env, AndroidJavaObject* instance)
{
    jclass cls = dmAndroid::LoadClass(env, "ru.rustore.defold.pay.RuStorePay");
    jfieldID instanceField = env->GetStaticFieldID(cls, "INSTANCE", "Lru/rustore/defold/pay/RuStorePay;");
    jobject obj = env->GetStaticObjectField(cls, instanceField);

    instance->cls = cls;
    instance->obj = obj;
}

static int GetUserAuthorizationStatus(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);

    dmAndroid::ThreadAttacher thread;
    JNIEnv* env = thread.GetEnv();

    AndroidJavaObject instance;
    GetJavaPayInstance(env, &instance);
    jmethodID method = env->GetMethodID(instance.cls, "getUserAuthorizationStatus", "()V");
    env->CallVoidMethod(instance.obj, method);
    instance.Free(env);
    
    return 0;
}

static int GetPurchaseAvailability(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);

    dmAndroid::ThreadAttacher thread;
    JNIEnv* env = thread.GetEnv();

    AndroidJavaObject instance;
    GetJavaPayInstance(env, &instance);
    jmethodID method = env->GetMethodID(instance.cls, "getPurchaseAvailability", "()V");
    env->CallVoidMethod(instance.obj, method);
    instance.Free(env);

    return 0;
}

static int GetProducts(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);

    std::vector<std::string> productIds;
    if (lua_istable(L, 1))
    {
        int tableSize = lua_objlen(L, 1);
        for (int i = 1; i <= tableSize; i++)
        {
            lua_rawgeti(L, 1, i);
            if (lua_isstring(L, -1))
            {
                const char* productId = lua_tostring(L, -1);
                productIds.push_back(productId);
            }
            lua_pop(L, 1);
        }
    }

    dmAndroid::ThreadAttacher thread;
    JNIEnv* env = thread.GetEnv();

    jobjectArray jproductIds = env->NewObjectArray(productIds.size(), env->FindClass("java/lang/String"), nullptr);
    for (int i = 0; i < productIds.size(); i++) {
        jstring jproductId = env->NewStringUTF(productIds[i].c_str());
        env->SetObjectArrayElement(jproductIds, i, jproductId);
        env->DeleteLocalRef(jproductId);
    }
    
    AndroidJavaObject instance;
    GetJavaPayInstance(env, &instance);
    jmethodID method = env->GetMethodID(instance.cls, "getProducts", "([Ljava/lang/String;)V");
    env->CallVoidMethod(instance.obj, method, jproductIds);
    instance.Free(env);
    
    env->DeleteLocalRef(jproductIds);
    
    return 0;
}

static int GetPurchases(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);

    dmAndroid::ThreadAttacher thread;
    JNIEnv* env = thread.GetEnv();

    const char* productType = "";
    const char* purchaseStatus = "";
    const char* acknowledgementState = "";

    if (lua_gettop(L) >= 1 && lua_istable(L, 1))
    {
        lua_getfield(L, 1, "productType");
        if (!lua_isnil(L, -1))
            productType = luaL_checkstring(L, -1);
        lua_pop(L, 1);

        lua_getfield(L, 1, "purchaseStatus");
        if (!lua_isnil(L, -1))
            purchaseStatus = luaL_checkstring(L, -1);
        lua_pop(L, 1);

        lua_getfield(L, 1, "acknowledgementState");
        if (!lua_isnil(L, -1))
            acknowledgementState = luaL_checkstring(L, -1);
        lua_pop(L, 1);
    }

    jstring jproductType = env->NewStringUTF(productType);
    jstring jpurchaseStatus = env->NewStringUTF(purchaseStatus);
    jstring jacknowledgementState = env->NewStringUTF(acknowledgementState);

    AndroidJavaObject instance;
    GetJavaPayInstance(env, &instance);
    jmethodID method = env->GetMethodID(instance.cls, "getPurchases", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
    env->CallVoidMethod(instance.obj, method, jproductType, jpurchaseStatus, jacknowledgementState);
    instance.Free(env);

    env->DeleteLocalRef(jproductType);
    env->DeleteLocalRef(jpurchaseStatus);
    env->DeleteLocalRef(jacknowledgementState);

    return 0;
}

static int GetPurchase(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);

    dmAndroid::ThreadAttacher thread;
    JNIEnv* env = thread.GetEnv();

    const char* productId = (char*)luaL_checkstring(L, 1);
    jstring jproductId = env->NewStringUTF(productId);
    
    AndroidJavaObject instance;
    GetJavaPayInstance(env, &instance);
    jmethodID method = env->GetMethodID(instance.cls, "getPurchase", "(Ljava/lang/String;)V");
    env->CallVoidMethod(instance.obj, method, jproductId);
    instance.Free(env);
    
    env->DeleteLocalRef(jproductId);

    return 0;
}

static int Purchase(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);

    dmAndroid::ThreadAttacher thread;
    JNIEnv* env = thread.GetEnv();

    const char* params = luaL_checkstring(L, 1);
    jstring jparams = env->NewStringUTF(params);

    const char* preferredPurchaseType = luaL_checkstring(L, 2);
    jstring jpreferredPurchaseType = env->NewStringUTF(preferredPurchaseType);

    const char* sdkTheme = "";
    bool enablePurchaseEventListener = false;
    
    int top = lua_gettop(L);
    bool arg3_is_theme = (top >= 3 && !lua_isnil(L, 3) && lua_type(L, 3) == LUA_TSTRING);
    bool arg3_is_bool  = (top >= 3 && !lua_isnil(L, 3) && !arg3_is_theme && (lua_type(L, 3) == LUA_TBOOLEAN || lua_type(L, 3) == LUA_TNUMBER));
    bool arg4_is_bool  = (top >= 4 && !lua_isnil(L, 4) && (lua_type(L, 4) == LUA_TBOOLEAN || lua_type(L, 4) == LUA_TNUMBER));
    
    if (arg3_is_theme) sdkTheme = lua_tostring(L, 3);
    
    if (arg4_is_bool) {
        enablePurchaseEventListener = (lua_type(L, 4) == LUA_TBOOLEAN) ? (lua_toboolean(L, 4) != 0) : (lua_tonumber(L, 4) != 0.0);
    } else if (arg3_is_bool) {
        enablePurchaseEventListener = (lua_type(L, 3) == LUA_TBOOLEAN) ? (lua_toboolean(L, 3) != 0) : (lua_tonumber(L, 3) != 0.0);
    }
    
    jstring jsdkTheme = env->NewStringUTF(sdkTheme);
    jboolean jenablePurchaseEventListener = (jboolean)enablePurchaseEventListener;
    
    AndroidJavaObject instance;
    GetJavaPayInstance(env, &instance);
    jmethodID method = env->GetMethodID(instance.cls, "purchase", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V");
    env->CallVoidMethod(instance.obj, method, jparams, jpreferredPurchaseType, jsdkTheme, jenablePurchaseEventListener);
    instance.Free(env);

    env->DeleteLocalRef(jparams);
    env->DeleteLocalRef(jpreferredPurchaseType);
    env->DeleteLocalRef(jsdkTheme);

    return 0;
}

static int PurchaseTwoStep(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);

    dmAndroid::ThreadAttacher thread;
    JNIEnv* env = thread.GetEnv();

    const char* params = luaL_checkstring(L, 1);
    jstring jparams = env->NewStringUTF(params);

    const char* sdkTheme = "";
    bool enablePurchaseEventListener = false;

    int top = lua_gettop(L);
    bool arg2_is_theme = (top >= 2 && !lua_isnil(L, 2) && lua_type(L, 2) == LUA_TSTRING);
    bool arg2_is_bool  = (top >= 2 && !lua_isnil(L, 2) && !arg2_is_theme && (lua_type(L, 2) == LUA_TBOOLEAN || lua_type(L, 2) == LUA_TNUMBER));
    bool arg3_is_bool  = (top >= 3 && !lua_isnil(L, 3) && (lua_type(L, 3) == LUA_TBOOLEAN || lua_type(L, 3) == LUA_TNUMBER));

    if (arg2_is_theme) sdkTheme = lua_tostring(L, 2);

    if (arg3_is_bool) {
        enablePurchaseEventListener = (lua_type(L, 3) == LUA_TBOOLEAN) ? (lua_toboolean(L, 3) != 0) : (lua_tonumber(L, 3) != 0.0);
    } else if (arg2_is_bool) {
        enablePurchaseEventListener = (lua_type(L, 2) == LUA_TBOOLEAN) ? (lua_toboolean(L, 2) != 0) : (lua_tonumber(L, 2) != 0.0);
    }

    jstring jsdkTheme = env->NewStringUTF(sdkTheme);
    jboolean jenablePurchaseEventListener = (jboolean)enablePurchaseEventListener;

    AndroidJavaObject instance;
    GetJavaPayInstance(env, &instance);
    jmethodID method = env->GetMethodID(instance.cls, "purchaseTwoStep", "(Ljava/lang/String;Ljava/lang/String;Z)V");
    env->CallVoidMethod(instance.obj, method, jparams, jsdkTheme, jenablePurchaseEventListener);
    instance.Free(env);

    env->DeleteLocalRef(jparams);
    env->DeleteLocalRef(jsdkTheme);

    return 0;
}

static int ConfirmTwoStepPurchase(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);

    dmAndroid::ThreadAttacher thread;
    JNIEnv* env = thread.GetEnv();

    const char* purchaseId = luaL_checkstring(L, 1);
    const char* developerPayload = lua_gettop(L) >= 2 && !lua_isnil(L, 2)
        ? lua_tostring(L, 2)
        : nullptr;
    
    jstring jpurchaseId = env->NewStringUTF(purchaseId);
    jstring jdeveloperPayload = developerPayload
        ? env->NewStringUTF(developerPayload)
        : nullptr;

    AndroidJavaObject instance;
    GetJavaPayInstance(env, &instance);
    jmethodID method = env->GetMethodID(instance.cls, "confirmTwoStepPurchase", "(Ljava/lang/String;Ljava/lang/String;)V");
    env->CallVoidMethod(instance.obj, method, jpurchaseId, jdeveloperPayload);
    instance.Free(env);

    env->DeleteLocalRef(jpurchaseId);
    if (jdeveloperPayload) env->DeleteLocalRef(jdeveloperPayload);

    return 0;
}

static int CancelTwoStepPurchase(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);

    dmAndroid::ThreadAttacher thread;
    JNIEnv* env = thread.GetEnv();

    const char* purchaseId = (char*)luaL_checkstring(L, 1);

    jstring jpurchaseId = env->NewStringUTF(purchaseId);

    AndroidJavaObject instance;
    GetJavaPayInstance(env, &instance);
    jmethodID method = env->GetMethodID(instance.cls, "cancelTwoStepPurchase", "(Ljava/lang/String;)V");
    env->CallVoidMethod(instance.obj, method, jpurchaseId);
    instance.Free(env);

    env->DeleteLocalRef(jpurchaseId);

    return 0;
}

static int UpdateAcknowledgementState(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);

    dmAndroid::ThreadAttacher thread;
    JNIEnv* env = thread.GetEnv();

    const char* purchaseId = luaL_checkstring(L, 1);
    const char* state = luaL_checkstring(L, 2);

    const char* developerPayload = nullptr;
    jstring jdeveloperPayload = nullptr;
    if (lua_gettop(L) >= 3 && !lua_isnil(L, 3))
    {
        developerPayload = luaL_checkstring(L, 3);
        jdeveloperPayload = env->NewStringUTF(developerPayload);
    }

    jstring jpurchaseId = env->NewStringUTF(purchaseId);
    jstring jstate = env->NewStringUTF(state);

    AndroidJavaObject instance;
    GetJavaPayInstance(env, &instance);
    jmethodID method = env->GetMethodID(instance.cls, "updateAcknowledgementState", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
    env->CallVoidMethod(instance.obj, method, jpurchaseId, jstate, jdeveloperPayload);
    instance.Free(env);

    env->DeleteLocalRef(jpurchaseId);
    env->DeleteLocalRef(jstate);
    if (jdeveloperPayload) env->DeleteLocalRef(jdeveloperPayload);

    return 0;
}

static int GetBillingSubscriptions(lua_State* L)
{
    DM_LUA_STACK_CHECK(L, 0);

    dmAndroid::ThreadAttacher thread;
    JNIEnv* env = thread.GetEnv();

    AndroidJavaObject instance;
    GetJavaPayInstance(env, &instance);
    jmethodID method = env->GetMethodID(instance.cls, "getBillingSubscriptions", "()V");
    env->CallVoidMethod(instance.obj, method);
    instance.Free(env);

    return 0;
}

// Functions exposed to Lua
static const luaL_reg Module_methods[] =
{
    {"get_user_authorization_status", GetUserAuthorizationStatus},
    {"get_purchase_availability", GetPurchaseAvailability},
    {"get_products", GetProducts},
    {"get_purchases", GetPurchases},
    {"get_purchase", GetPurchase},
    {"purchase", Purchase},
    {"purchase_two_step", PurchaseTwoStep},
    {"confirm_two_step_purchase", ConfirmTwoStepPurchase},
    {"cancel_two_step_purchase", CancelTwoStepPurchase},
    {"update_acknowledgement_state", UpdateAcknowledgementState},
    {"get_billing_subscriptions", GetBillingSubscriptions},
    {0, 0}
};

#else

static const luaL_reg Module_methods[] =
{
    {0, 0}
};

#endif

static void LuaInit(lua_State* L)
{
    int top = lua_gettop(L);
    luaL_register(L, MODULE_NAME, Module_methods);
    lua_pop(L, 1);
    assert(top == lua_gettop(L));
}

static dmExtension::Result AppInitializeExtension(dmExtension::AppParams* params)
{
    if (DEBUG) dmLogInfo("AppInitializeExtension");
    return dmExtension::RESULT_OK;
}

static dmExtension::Result InitializeExtension(dmExtension::Params* params)
{
    LuaInit(params->m_L);
    RegisterGlobalRuStorePayEnums(params->m_L);
    
    if (DEBUG) dmLogInfo("Registered %s Extension", MODULE_NAME);
    return dmExtension::RESULT_OK;
}

static dmExtension::Result AppFinalizeExtension(dmExtension::AppParams* params)
{
    if (DEBUG) dmLogInfo("AppFinalizeExtension");
    return dmExtension::RESULT_OK;
}

static dmExtension::Result FinalizeExtension(dmExtension::Params* params)
{
    if (DEBUG) dmLogInfo("FinalizeExtension");
    return dmExtension::RESULT_OK;
}

static dmExtension::Result OnUpdateExtension(dmExtension::Params* params)
{
    if (DEBUG) dmLogInfo("OnUpdateExtension");
    return dmExtension::RESULT_OK;
}

static void OnEventExtension(dmExtension::Params* params, const dmExtension::Event* event)
{
    if (DEBUG)
    {
        switch(event->m_Event)
        {
            case dmExtension::EVENT_ID_ACTIVATEAPP:
                dmLogInfo("OnEventExtension - EVENT_ID_ACTIVATEAPP");
                break;
            case dmExtension::EVENT_ID_DEACTIVATEAPP:
                dmLogInfo("OnEventExtension - EVENT_ID_DEACTIVATEAPP");
                break;
            case dmExtension::EVENT_ID_ICONIFYAPP:
                dmLogInfo("OnEventExtension - EVENT_ID_ICONIFYAPP");
                break;
            case dmExtension::EVENT_ID_DEICONIFYAPP:
                dmLogInfo("OnEventExtension - EVENT_ID_DEICONIFYAPP");
                break;
            default:
                dmLogWarning("OnEventExtension - Unknown event id");
                break;
        }
    }
}

// Defold SDK uses a macro for setting up extension entry points:
//
// DM_DECLARE_EXTENSION(symbol, name, app_init, app_final, init, update, on_event, final)

// Extension is the C++ symbol that holds all relevant extension data.
// It must match the name field in the `ext.manifest`
DM_DECLARE_EXTENSION(EXTENSION_NAME, LIB_NAME, AppInitializeExtension, AppFinalizeExtension, InitializeExtension, OnUpdateExtension, OnEventExtension, FinalizeExtension)
