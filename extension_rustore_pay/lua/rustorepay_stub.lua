-- Stub for Defold Editor (autocomplete + diagnostics).
-- Runtime module is provided by native extension via luaL_register(MODULE_NAME, Module_methods).
-- Do not require this file.

---@class rustorepay
local M = {}

--- Запросить статус авторизации пользователя.
--- Результат придёт асинхронно (через ваш механизм событий/коллбеков на стороне расширения).
function M.get_user_authorization_status() end

--- Проверить доступность покупок.
--- Результат придёт асинхронно.
function M.get_purchase_availability() end

--- Запросить список продуктов по их id.
--- @param product_ids string[] @Lua-массив строк: {"id1","id2",...}
function M.get_products(product_ids) end

---@class rustorepay.GetPurchasesParams
---@field productType string|nil @RuStorePayEnums.ProductType.* (например RuStorePayEnums.ProductType.SUBSCRIPTION)
---@field purchaseStatus string|nil @Один из статусов: RuStorePayEnums.ProductPurchaseStatus.* / RuStorePayEnums.SubscriptionPurchaseStatus.* (в зависимости от типа)
---@field acknowledgementState string|nil @RuStorePayEnums.AcknowledgementState.* (например RuStorePayEnums.AcknowledgementState.PENDING)

--- Запросить покупки с фильтрами.
--- @param params rustorepay.GetPurchasesParams|nil
function M.get_purchases(params) end

--- Запросить покупку по product_id.
--- @param product_id string
function M.get_purchase(product_id) end

--- Совершить покупку.
---
--- @param params_json string @JSON-строка параметров покупки
--- @param preferred_purchase_type string @RuStorePayEnums.PreferredPurchaseType.* (рекомендуется)
--- @param sdk_theme string|nil @RuStorePayEnums.SdkTheme.* (например RuStorePayEnums.SdkTheme.DARK)
--- @param enable_purchase_event_listener boolean|nil @включить PurchaseEventListener
function M.purchase(params_json, preferred_purchase_type, sdk_theme, enable_purchase_event_listener) end

--- Покупка в два шага.
---
--- @param params_json string @JSON-строка параметров покупки
--- @param sdk_theme string|nil @RuStorePayEnums.SdkTheme.* (например RuStorePayEnums.SdkTheme.DARK)
--- @param enable_purchase_event_listener boolean|nil @включить PurchaseEventListener
function M.purchase_two_step(params_json, sdk_theme, enable_purchase_event_listener) end

--- Подтвердить двухшаговую покупку.
--- @param purchase_id string
--- @param developer_payload string|nil
function M.confirm_two_step_purchase(purchase_id, developer_payload) end

--- Отменить двухшаговую покупку.
--- @param purchase_id string
function M.cancel_two_step_purchase(purchase_id) end

--- Обновить состояние подтверждения покупки.
--- @param purchase_id string
--- @param state string @RuStorePayEnums.AcknowledgementState.* (например RuStorePayEnums.AcknowledgementState.ACKNOWLEDGED)
--- @param developer_payload string|nil
function M.update_acknowledgement_state(purchase_id, state, developer_payload) end

--- Получить список подписок, оформленных в SDK Billing Client.
function M.get_billing_subscriptions() end

---@type rustorepay
rustorepay = rustorepay
