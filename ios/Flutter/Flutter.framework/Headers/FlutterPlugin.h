// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef FLUTTER_FLUTTERPLUGIN_H_
#define FLUTTER_FLUTTERPLUGIN_H_

#import <UIKit/UIKit.h>

#include "FlutterBinaryMessenger.h"
#include "FlutterChannels.h"
#include "FlutterCodecs.h"
#include "FlutterPlatformViews.h"
#include "FlutterTexture.h"

NS_ASSUME_NONNULL_BEGIN
@protocol FlutterPluginRegistrar;

/**
 Implemented by the iOS part of a Flutter plugin.

 Defines a set of optional callback methods and a method to set up the plugin
 and register it to be called by other application components.
 */
@protocol FlutterPlugin <NSObject>
@required
/**
 Registers this plugin using the context information and callback registration
 methods exposed by the given registrar.

 The registrar is obtained from a `FlutterPluginRegistry` which keeps track of
 the identity of registered plugins and provides basic support for cross-plugin
 coordination.

 The caller of this method, a plugin registrant, is usually autogenerated by
 Flutter tooling based on declared plugin dependencies. The generated registrant
 asks the registry for a registrar for each plugin, and calls this method to
 allow the plugin to initialize itself and register callbacks with application
 objects available through the registrar protocol.

 - Parameters:
   - registrar: A helper providing application context and methods for
     registering callbacks.
 */
+ (void)registerWithRegistrar:(NSObject<FlutterPluginRegistrar>*)registrar;
@optional
/**
 Called if this plugin has been registered to receive `FlutterMethodCall`s.

 - Parameters:
   - call: The method call command object.
   - result: A callback for submitting the result of the call.
 */
- (void)handleMethodCall:(FlutterMethodCall*)call result:(FlutterResult)result;

/**
 Called if this plugin has been registered for `UIApplicationDelegate` callbacks.

 - Returns: `NO` if this plugin vetoes application launch.
 */
- (BOOL)application:(UIApplication*)application
    didFinishLaunchingWithOptions:(NSDictionary*)launchOptions;

/**
 Called if this plugin has been registered for `UIApplicationDelegate` callbacks.

 - Returns: `NO` if this plugin vetoes application launch.
 */
- (BOOL)application:(UIApplication*)application
    willFinishLaunchingWithOptions:(NSDictionary*)launchOptions;

/**
 Called if this plugin has been registered for `UIApplicationDelegate` callbacks.
 */
- (void)applicationDidBecomeActive:(UIApplication*)application;

/**
 Called if this plugin has been registered for `UIApplicationDelegate` callbacks.
 */
- (void)applicationWillResignActive:(UIApplication*)application;

/**
 Called if this plugin has been registered for `UIApplicationDelegate` callbacks.
 */
- (void)applicationDidEnterBackground:(UIApplication*)application;

/**
 Called if this plugin has been registered for `UIApplicationDelegate` callbacks.
 */
- (void)applicationWillEnterForeground:(UIApplication*)application;

/**
 Called if this plugin has been registered for `UIApplicationDelegate` callbacks.
 */
- (void)applicationWillTerminate:(UIApplication*)application;

/**
 Called if this plugin has been registered for `UIApplicationDelegate` callbacks.
 */
- (void)application:(UIApplication*)application
    didRegisterUserNotificationSettings:(UIUserNotificationSettings*)notificationSettings;

/**
 Called if this plugin has been registered for `UIApplicationDelegate` callbacks.
 */
- (void)application:(UIApplication*)application
    didRegisterForRemoteNotificationsWithDeviceToken:(NSData*)deviceToken;

/**
 Called if this plugin has been registered for `UIApplicationDelegate` callbacks.

 - Returns: `YES` if this plugin handles the request.
 */
- (BOOL)application:(UIApplication*)application
    didReceiveRemoteNotification:(NSDictionary*)userInfo
          fetchCompletionHandler:(void (^)(UIBackgroundFetchResult result))completionHandler;

/**
 Called if this plugin has been registered for `UIApplicationDelegate` callbacks.

  - Returns: `YES` if this plugin handles the request.
*/
- (BOOL)application:(UIApplication*)application
            openURL:(NSURL*)url
            options:(NSDictionary<UIApplicationOpenURLOptionsKey, id>*)options;

/**
 Called if this plugin has been registered for `UIApplicationDelegate` callbacks.

 - Returns: `YES` if this plugin handles the request.
 */
- (BOOL)application:(UIApplication*)application handleOpenURL:(NSURL*)url;

/**
 Called if this plugin has been registered for `UIApplicationDelegate` callbacks.

  - Returns: `YES` if this plugin handles the request.
*/
- (BOOL)application:(UIApplication*)application
              openURL:(NSURL*)url
    sourceApplication:(NSString*)sourceApplication
           annotation:(id)annotation;

/**
 Called if this plugin has been registered for `UIApplicationDelegate` callbacks.

  - Returns: `YES` if this plugin handles the request.
*/
- (BOOL)application:(UIApplication*)application
    performActionForShortcutItem:(UIApplicationShortcutItem*)shortcutItem
               completionHandler:(void (^)(BOOL succeeded))completionHandler
    API_AVAILABLE(ios(9.0));

/**
 Called if this plugin has been registered for `UIApplicationDelegate` callbacks.

 - Returns: `YES` if this plugin handles the request.
 */
- (BOOL)application:(UIApplication*)application
    handleEventsForBackgroundURLSession:(nonnull NSString*)identifier
                      completionHandler:(nonnull void (^)(void))completionHandler;

/**
 Called if this plugin has been registered for `UIApplicationDelegate` callbacks.

 - Returns: `YES` if this plugin handles the request.
 */
- (BOOL)application:(UIApplication*)application
    performFetchWithCompletionHandler:(void (^)(UIBackgroundFetchResult result))completionHandler;

/**
 Called if this plugin has been registered for `UIApplicationDelegate` callbacks.

 - Returns: `YES` if this plugin handles the request.
 */
- (BOOL)application:(UIApplication*)application
    continueUserActivity:(NSUserActivity*)userActivity
      restorationHandler:(void (^)(NSArray*))restorationHandler;
@end

/**
 Registration context for a single `FlutterPlugin`, providing a one stop shop
 for the plugin to access contextual information and register callbacks for
 various application events.

 Registrars are obtained from a `FlutterPluginRegistry` which keeps track of
 the identity of registered plugins and provides basic support for cross-plugin
 coordination.
 */
@protocol FlutterPluginRegistrar <NSObject>
/**
 Returns a `FlutterBinaryMessenger` for creating Dart/iOS communication
 channels to be used by the plugin.

 - Returns: The messenger.
 */
- (NSObject<FlutterBinaryMessenger>*)messenger;

/**
 Returns a `FlutterTextureRegistry` for registering textures
 provided by the plugin.

 - Returns: The texture registry.
 */
- (NSObject<FlutterTextureRegistry>*)textures;

/**
 * Registers a `FlutterPlatformViewFactory` for creation of platfrom views.
 *
 * Plugins expose `UIView` for embedding in Flutter apps by registering a view factory.
 *
 * @param factory The view factory that will be registered.
 * @param factoryId:: A unique identifier for the factory, the Dart code of the Flutter app can use
 *   this identifier to request creation of a `UIView` by the registered factory.
 */
- (void)registerViewFactory:(NSObject<FlutterPlatformViewFactory>*)factory
                     withId:(NSString*)factoryId;

/**
 Publishes a value for external use of the plugin.

 Plugins may publish a single value, such as an instance of the
 plugin's main class, for situations where external control or
 interaction is needed.

 The published value will be available from the `FlutterPluginRegistry`.
 Repeated calls overwrite any previous publication.

 - Parameter value: The value to be published.
 */
- (void)publish:(NSObject*)value;

/**
 Registers the plugin as a receiver of incoming method calls from the Dart side
 on the specified `FlutterMethodChannel`.

 - Parameters:
   - delegate: The receiving object, such as the plugin's main class.
   - channel: The channel
 */
- (void)addMethodCallDelegate:(NSObject<FlutterPlugin>*)delegate
                      channel:(FlutterMethodChannel*)channel;

/**
 Registers the plugin as a receiver of `UIApplicationDelegate` calls.

 - Parameters delegate: The receiving object, such as the plugin's main class.
 */
- (void)addApplicationDelegate:(NSObject<FlutterPlugin>*)delegate;

/**
 Returns the file name for the given asset.
 The returned file name can be used to access the asset in the application's main bundle.

 - Parameter asset: The name of the asset. The name can be hierarchical.
 - Returns: the file name to be used for lookup in the main bundle.
 */
- (NSString*)lookupKeyForAsset:(NSString*)asset;

/**
 Returns the file name for the given asset which originates from the specified package.
 The returned file name can be used to access the asset in the application's main bundle.

 - Parameters:
   - asset: The name of the asset. The name can be hierarchical.
   - package: The name of the package from which the asset originates.
 - Returns: the file name to be used for lookup in the main bundle.
 */
- (NSString*)lookupKeyForAsset:(NSString*)asset fromPackage:(NSString*)package;
@end

/**
 A registry of Flutter iOS plugins.

 Plugins are identified by unique string keys, typically the name of the
 plugin's main class. The registry tracks plugins by this key, mapping it to
 a value published by the plugin during registration, if any. This provides a
 very basic means of cross-plugin coordination with loose coupling between
 unrelated plugins.

 Plugins typically need contextual information and the ability to register
 callbacks for various application events. To keep the API of the registry
 focused, these facilities are not provided directly by the registry, but by
 a `FlutterPluginRegistrar`, created by the registry in exchange for the unique
 key of the plugin.

 There is no implied connection between the registry and the registrar.
 Specifically, callbacks registered by the plugin via the registrar may be
 relayed directly to the underlying iOS application objects.
 */
@protocol FlutterPluginRegistry <NSObject>
/**
 Returns a registrar for registering a plugin.

 - Parameter pluginKey: The unique key identifying the plugin.
 */
- (NSObject<FlutterPluginRegistrar>*)registrarForPlugin:(NSString*)pluginKey;
/**
 Returns whether the specified plugin has been registered.

 - Parameter pluginKey: The unique key identifying the plugin.
 - Returns: `YES` if `registrarForPlugin` has been called with `pluginKey`.
 */
- (BOOL)hasPlugin:(NSString*)pluginKey;

/**
 Returns a value published by the specified plugin.

 - Parameter pluginKey: The unique key identifying the plugin.
 - Returns: An object published by the plugin, if any. Will be `NSNull` if
   nothing has been published. Will be `nil` if the plugin has not been
   registered.
 */
- (NSObject*)valuePublishedByPlugin:(NSString*)pluginKey;
@end

/**
 Implement this in the `UIAppDelegate` of your app to enable Flutter plugins to register themselves
 to the application life cycle events.
*/
@protocol FlutterAppLifeCycleProvider
- (void)addApplicationLifeCycleDelegate:(NSObject<FlutterPlugin>*)delegate;
@end

NS_ASSUME_NONNULL_END;

#endif  // FLUTTER_FLUTTERPLUGIN_H_