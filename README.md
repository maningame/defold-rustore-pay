# defold-rustore-pay

Платежи и подписки RuStore Pay SDK для Defold — расширение `RuStorePay`, Lua-модуль `rustorepay` и глобал
`RuStorePayEnums`. Официальный плагин [rustore-defold-pay](https://gitflic.ru/project/rustore/rustore-defold-pay),
упакованный в библиотеку Defold: на GitFlic он ставится копированием папок, отсюда — строкой в `dependencies`.

| | |
|---|---|
| SDK | `ru.rustore.sdk:pay:11.1.0` |
| Источник | rustore-defold-pay, `master` от 08.09.2026 (`628b24b`) |
| Нужен core | [defold-rustore-core](https://github.com/maningame/defold-rustore-core) `10.5.0-1` |
| Платформы | Android, Defold 1.9.2+; на остальных — пустой модуль (так у RuStore) |
| Документация | [rustore.ru/help/sdk/pay/defold/11-1-0](https://www.rustore.ru/help/sdk/pay/defold/11-1-0) |

## Подключение

1. В `[project] dependencies` Android-цели (`platforms/<цель>/platform.settings`) —
   вместе с core, сам Defold его не подтянет:

   ```ini
   dependencies#N = https://github.com/maningame/defold-rustore-core/archive/refs/tags/10.5.0-1.zip
   dependencies#M = https://github.com/maningame/defold-rustore-pay/archive/refs/tags/11.1.0.zip
   ```

2. В манифест игры — активити диплинка `ru.rustore.defold.pay.RuStoreIntentFilterActivity`, переопределение
   `PayActivity` и три `meta-data`. Образец — `extension_rustore_pay/manifests/android/ExtendedAndroidManifest.xml`
   (шаблон манифеста демо RuStore; сам он в сборку не попадает).
3. В ресурсы игры (`bundle_resources`, `android/res/values/*.xml`) — строки, на которые ссылается манифест:

   ```xml
   <string name="rustore_PayClientSettings_consoleApplicationId" translatable="false">ID приложения в консоли</string>
   <string name="rustore_PayClientSettings_internalConfigKey" translatable="false">defold</string>
   <string name="rustore_PayClientSettings_deeplinkScheme" translatable="false">схема диплинка</string>
   ```

## Lua

Вызовы — `rustorepay.*`, ответы приходят в каналы `rustore_pay_on_*` через `rustorecore.connect`:

```lua
rustorecore.connect("rustore_pay_on_purchase_success", on_purchase_success)
rustorecore.connect("rustore_pay_on_purchase_failure", on_purchase_failure)
rustorepay.purchase(json.encode({ productId = "coins_100" }), RuStorePayEnums.PreferredPurchaseType.ONE_STEP)
```

Аннотации — `extension_rustore_pay/lua/*_stub.lua`.

## Отличия от GitFlic

Нет: папка `extension_rustore_pay` — как в `master` RuStore.

## Обновление с GitFlic

Скриптом `tools/rustore.js` из клона defold-kb рядом с этой репой; по шагам — скилл `/rustore-update`.

```
node tools/rustore.js check                   # что нового у RuStore
node tools/rustore.js update pay              # папка с GitFlic поверх наших отличий
node tools/rustore.js verify --bob <bob.jar>  # сборка под Linux, Windows, macOS и Android
```

Откуда снята папка — `gitflic.json`. Отличия от GitFlic скрипт переносит трёхсторонним слиянием, конфликт —
только там, где RuStore поменял те же строки. Тег — версия SDK, наша правка поверх той же версии —
`<версия>-1`, `<версия>-2`.

## Лицензия

MIT, © RuStore — [MIT-LICENSE.txt](MIT-LICENSE.txt).
