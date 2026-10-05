#pragma once

// X-macro списки: (KEY, VALUE)

#define PAY_ENUM_PURCHASE_TYPE(X) \
X(ONE_STEP, "ONE_STEP")       \
X(TWO_STEP, "TWO_STEP")       \
X(UNDEFINED, "UNDEFINED")

#define PAY_ENUM_PREFERRED_PURCHASE_TYPE(X) \
X(ONE_STEP, "ONE_STEP")                 \
X(TWO_STEP, "TWO_STEP")

#define PAY_ENUM_USER_AUTH_STATUS(X) \
X(AUTHORIZED, "AUTHORIZED")      \
X(UNAUTHORIZED, "UNAUTHORIZED")

#define PAY_ENUM_PRODUCT_TYPE(X) \
X(NON_CONSUMABLE_PRODUCT, "NON_CONSUMABLE_PRODUCT") \
X(CONSUMABLE_PRODUCT, "CONSUMABLE_PRODUCT")         \
X(SUBSCRIPTION, "SUBSCRIPTION")

#define PAY_ENUM_APPLICATION_PURCHASE_STATUS(X) \
X(INVOICE_CREATED, "ApplicationPurchaseStatus.INVOICE_CREATED") \
X(CANCELLED, "ApplicationPurchaseStatus.CANCELLED")             \
X(PROCESSING, "ApplicationPurchaseStatus.PROCESSING")           \
X(REJECTED, "ApplicationPurchaseStatus.REJECTED")               \
X(CONFIRMED, "ApplicationPurchaseStatus.CONFIRMED")             \
X(CONSUMED, "ApplicationPurchaseStatus.CONSUMED")               \
X(REFUNDED, "ApplicationPurchaseStatus.REFUNDED")               \
X(EXECUTING, "ApplicationPurchaseStatus.EXECUTING")             \
X(EXPIRED, "ApplicationPurchaseStatus.EXPIRED")                 \
X(PAID, "ApplicationPurchaseStatus.PAID")                       \
X(REVERSED, "ApplicationPurchaseStatus.REVERSED")

#define PAY_ENUM_PRODUCT_PURCHASE_STATUS(X) \
X(INVOICE_CREATED, "ProductPurchaseStatus.INVOICE_CREATED") \
X(CANCELLED, "ProductPurchaseStatus.CANCELLED")             \
X(PROCESSING, "ProductPurchaseStatus.PROCESSING")           \
X(REJECTED, "ProductPurchaseStatus.REJECTED")               \
X(CONFIRMED, "ProductPurchaseStatus.CONFIRMED")             \
X(REFUNDED, "ProductPurchaseStatus.REFUNDED")               \
X(REFUNDING, "ProductPurchaseStatus.REFUNDING")             \
X(EXECUTING, "ProductPurchaseStatus.EXECUTING")             \
X(EXPIRED, "ProductPurchaseStatus.EXPIRED")                 \
X(PAID, "ProductPurchaseStatus.PAID")                       \
X(REVERSED, "ProductPurchaseStatus.REVERSED")

#define PAY_ENUM_SUBSCRIPTION_PURCHASE_STATUS(X) \
X(INVOICE_CREATED, "SubscriptionPurchaseStatus.INVOICE_CREATED") \
X(CANCELLED, "SubscriptionPurchaseStatus.CANCELLED")             \
X(EXPIRED, "SubscriptionPurchaseStatus.EXPIRED")                 \
X(PROCESSING, "SubscriptionPurchaseStatus.PROCESSING")           \
X(REJECTED, "SubscriptionPurchaseStatus.REJECTED")               \
X(ACTIVE, "SubscriptionPurchaseStatus.ACTIVE")                   \
X(PAUSED, "SubscriptionPurchaseStatus.PAUSED")                   \
X(TERMINATED, "SubscriptionPurchaseStatus.TERMINATED")           \
X(CLOSED, "SubscriptionPurchaseStatus.CLOSED")

#define PAY_ENUM_SDK_THEME(X) \
X(LIGHT, "LIGHT")         \
X(DARK, "DARK")

#define PAY_ENUM_ACKNOWLEDGEMENT_STATE(X) \
X(PENDING, "PENDING")         \
X(ACKNOWLEDGED, "ACKNOWLEDGED") \
X(UNKNOWN, "UNKNOWN")
