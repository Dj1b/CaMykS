<?php

$mapping = array(
    'Payline\PaylineSDK' => __DIR__ . '/PaylineSDK.php',
    'Payline\SoapVarFactory' => __DIR__ . '/SoapVarFactory.php',
    'Payline\WebserviceClient' => __DIR__ . '/WebserviceClient.php',

    /*
    'Payline\Cache\Apc' => __DIR__ . '/Cache/Apc.php',
    'Payline\Cache\CacheInterface' => __DIR__ . '/Cache/CacheInterface.php',
    'Payline\Cache\CacheTrait' => __DIR__ . '/Cache/CacheTrait.php',
    'Payline\Cache\File' => __DIR__ . '/Cache/File.php',
    */

    'Payline\Objects\Address' => __DIR__ . '/Objects/Address.php',
    'Payline\Objects\AddressOwner' => __DIR__ . '/Objects/AddressOwner.php',
    'Payline\Objects\Authentication3DSecure' => __DIR__ . '/Objects/Authentication3DSecure.php',
    'Payline\Objects\Authorization' => __DIR__ . '/Objects/Authorization.php',
    'Payline\Objects\BankAccountData' => __DIR__ . '/Objects/BankAccountData.php',
    'Payline\Objects\BillingRecordForUpdate' => __DIR__ . '/Objects/BillingRecordForUpdate.php',
    'Payline\Objects\Buyer' => __DIR__ . '/Objects/Buyer.php',
    'Payline\Objects\Card' => __DIR__ . '/Objects/Card.php',
    'Payline\Objects\Cheque' => __DIR__ . '/Objects/Cheque.php',
    'Payline\Objects\Creditor' => __DIR__ . '/Objects/Creditor.php',
    'Payline\Objects\Order' => __DIR__ . '/Objects/Order.php',
    'Payline\Objects\OrderDetail' => __DIR__ . '/Objects/OrderDetail.php',
    'Payline\Objects\Owner' => __DIR__ . '/Objects/Owner.php',
    'Payline\Objects\Payment' => __DIR__ . '/Objects/Payment.php',
    'Payline\Objects\PrivateData' => __DIR__ . '/Objects/PrivateData.php',
    'Payline\Objects\PrivateDataList' => __DIR__ . '/Objects/PrivateDataList.php',
    'Payline\Objects\Reattempt' => __DIR__ . '/Objects/Reattempt.php',
    'Payline\Objects\Recurring' => __DIR__ . '/Objects/Recurring.php',
    'Payline\Objects\SelectedContractList' => __DIR__ . '/Objects/SelectedContractList.php',
    'Payline\Objects\SubMerchant' => __DIR__ . '/Objects/SubMerchant.php',
    'Payline\Objects\ThreeDSInfo' => __DIR__ . '/Objects/ThreeDSInfo.php',
    'Payline\Objects\Wallet' => __DIR__ . '/Objects/Wallet.php',
    'Payline\Objects\WalletIdList' => __DIR__ . '/Objects/WalletIdList.php',
    'Payline\Objects\contractNumberWalletList' => __DIR__ . '/Objects/contractNumberWalletList.php',

    'Payline\Objects\Buyer\BillingAddress' => __DIR__ . '/Objects/Buyer/BillingAddress.php',
    'Payline\Objects\Buyer\MerchantAuthentication' => __DIR__ . '/Objects/Buyer/MerchantAuthentication.php',
    'Payline\Objects\Buyer\ShippingAdress' => __DIR__ . '/Objects/Buyer/ShippingAdress.php',

    'Payline\Objects\Card\PaymentData' => __DIR__ . '/Objects/Card/PaymentData.php',

    'Payline\Objects\Owner\BillingAddress' => __DIR__ . '/Objects/Owner/BillingAddress.php',

    'Payline\Objects\ThreeDSInfo\Browser' => __DIR__ . '/Objects/ThreeDSInfo/Browser.php',
    'Payline\Objects\ThreeDSInfo\Sdk' => __DIR__ . '/Objects/ThreeDSInfo/Sdk.php',

    'Payline\Objects\Wallet\ShippingAddress' => __DIR__ . '/Objects/Wallet/ShippingAddress.php',
);

spl_autoload_register(function ($class) use ($mapping) {
    if (isset($mapping[$class])) {
        require $mapping[$class];
    }
}, true);
