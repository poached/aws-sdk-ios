//
// Copyright 2010-2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License").
// You may not use this file except in compliance with the License.
// A copy of the License is located at
//
// http://aws.amazon.com/apache2.0
//
// or in the "license" file accompanying this file. This file is distributed
// on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
// express or implied. See the License for the specific language governing
// permissions and limitations under the License.
//

#import <Foundation/Foundation.h>
#import <AWSCore/AWSCore.h>
#import "AWSAutoScalingModel.h"
#import "AWSAutoScalingResources.h"

NS_ASSUME_NONNULL_BEGIN

//! SDK version for AWSAutoScaling
FOUNDATION_EXPORT NSString *const AWSAutoScalingSDKVersion;

/**
 <fullname>Amazon EC2 Auto Scaling</fullname><p>Amazon EC2 Auto Scaling is designed to automatically launch or terminate EC2 instances based on user-defined scaling policies, scheduled actions, and health checks. Use this service with AWS Auto Scaling, Amazon CloudWatch, and Elastic Load Balancing.</p><p>For more information, including information about granting IAM users required permissions for Amazon EC2 Auto Scaling actions, see the <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/what-is-amazon-ec2-auto-scaling.html">Amazon EC2 Auto Scaling User Guide</a>.</p>
 */
@interface AWSAutoScaling : AWSService

/**
 The service configuration used to instantiate this service client.
 
 @warning Once the client is instantiated, do not modify the configuration object. It may cause unspecified behaviors.
 */
@property (nonatomic, strong, readonly) AWSServiceConfiguration *configuration;

/**
 Returns the singleton service client. If the singleton object does not exist, the SDK instantiates the default service client with `defaultServiceConfiguration` from `[AWSServiceManager defaultServiceManager]`. The reference to this object is maintained by the SDK, and you do not need to retain it manually.

 For example, set the default service configuration in `- application:didFinishLaunchingWithOptions:`
 
 *Swift*

     func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
        let credentialProvider = AWSCognitoCredentialsProvider(regionType: .USEast1, identityPoolId: "YourIdentityPoolId")
        let configuration = AWSServiceConfiguration(region: .USEast1, credentialsProvider: credentialProvider)
        AWSServiceManager.default().defaultServiceConfiguration = configuration
 
        return true
    }

 *Objective-C*

     - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
          AWSCognitoCredentialsProvider *credentialsProvider = [[AWSCognitoCredentialsProvider alloc] initWithRegionType:AWSRegionUSEast1
                                                                                                          identityPoolId:@"YourIdentityPoolId"];
          AWSServiceConfiguration *configuration = [[AWSServiceConfiguration alloc] initWithRegion:AWSRegionUSEast1
                                                                               credentialsProvider:credentialsProvider];
          [AWSServiceManager defaultServiceManager].defaultServiceConfiguration = configuration;

          return YES;
      }

 Then call the following to get the default service client:

 *Swift*

     let AutoScaling = AWSAutoScaling.default()

 *Objective-C*

     AWSAutoScaling *AutoScaling = [AWSAutoScaling defaultAutoScaling];

 @return The default service client.
 */
+ (instancetype)defaultAutoScaling;

/**
 Creates a service client with the given service configuration and registers it for the key.

 For example, set the default service configuration in `- application:didFinishLaunchingWithOptions:`

 *Swift*

     func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
        let credentialProvider = AWSCognitoCredentialsProvider(regionType: .USEast1, identityPoolId: "YourIdentityPoolId")
        let configuration = AWSServiceConfiguration(region: .USWest2, credentialsProvider: credentialProvider)
        AWSAutoScaling.register(with: configuration!, forKey: "USWest2AutoScaling")
 
        return true
    }

 *Objective-C*

     - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
         AWSCognitoCredentialsProvider *credentialsProvider = [[AWSCognitoCredentialsProvider alloc] initWithRegionType:AWSRegionUSEast1
                                                                                                         identityPoolId:@"YourIdentityPoolId"];
         AWSServiceConfiguration *configuration = [[AWSServiceConfiguration alloc] initWithRegion:AWSRegionUSWest2
                                                                              credentialsProvider:credentialsProvider];

         [AWSAutoScaling registerAutoScalingWithConfiguration:configuration forKey:@"USWest2AutoScaling"];

         return YES;
     }

 Then call the following to get the service client:

 *Swift*

     let AutoScaling = AWSAutoScaling(forKey: "USWest2AutoScaling")

 *Objective-C*

     AWSAutoScaling *AutoScaling = [AWSAutoScaling AutoScalingForKey:@"USWest2AutoScaling"];

 @warning After calling this method, do not modify the configuration object. It may cause unspecified behaviors.

 @param configuration A service configuration object.
 @param key           A string to identify the service client.
 */
+ (void)registerAutoScalingWithConfiguration:(AWSServiceConfiguration *)configuration forKey:(NSString *)key;

/**
 Retrieves the service client associated with the key. You need to call `+ registerAutoScalingWithConfiguration:forKey:` before invoking this method.

 For example, set the default service configuration in `- application:didFinishLaunchingWithOptions:`

 *Swift*

     func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
        let credentialProvider = AWSCognitoCredentialsProvider(regionType: .USEast1, identityPoolId: "YourIdentityPoolId")
        let configuration = AWSServiceConfiguration(region: .USWest2, credentialsProvider: credentialProvider)
        AWSAutoScaling.register(with: configuration!, forKey: "USWest2AutoScaling")
 
        return true
    }

 *Objective-C*

     - (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
         AWSCognitoCredentialsProvider *credentialsProvider = [[AWSCognitoCredentialsProvider alloc] initWithRegionType:AWSRegionUSEast1
                                                                                                         identityPoolId:@"YourIdentityPoolId"];
         AWSServiceConfiguration *configuration = [[AWSServiceConfiguration alloc] initWithRegion:AWSRegionUSWest2
                                                                              credentialsProvider:credentialsProvider];

         [AWSAutoScaling registerAutoScalingWithConfiguration:configuration forKey:@"USWest2AutoScaling"];

         return YES;
     }

 Then call the following to get the service client:

 *Swift*

     let AutoScaling = AWSAutoScaling(forKey: "USWest2AutoScaling")

 *Objective-C*

     AWSAutoScaling *AutoScaling = [AWSAutoScaling AutoScalingForKey:@"USWest2AutoScaling"];

 @param key A string to identify the service client.

 @return An instance of the service client.
 */
+ (instancetype)AutoScalingForKey:(NSString *)key;

/**
 Removes the service client associated with the key and release it.
 
 @warning Before calling this method, make sure no method is running on this client.
 
 @param key A string to identify the service client.
 */
+ (void)removeAutoScalingForKey:(NSString *)key;

/**
 <p>Attaches one or more EC2 instances to the specified Auto Scaling group.</p><p>When you attach instances, Amazon EC2 Auto Scaling increases the desired capacity of the group by the number of instances being attached. If the number of instances being attached plus the desired capacity of the group exceeds the maximum size of the group, the operation fails.</p><p>If there is a Classic Load Balancer attached to your Auto Scaling group, the instances are also registered with the load balancer. If there are target groups attached to your Auto Scaling group, the instances are also registered with the target groups.</p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/attach-instance-asg.html">Attach EC2 instances to your Auto Scaling group</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the AttachInstances service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will be `nil`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`, `AWSAutoScalingErrorServiceLinkedRoleFailure`.
 
 @see AWSAutoScalingAttachInstancesQuery
 */
- (AWSTask *)attachInstances:(AWSAutoScalingAttachInstancesQuery *)request;

/**
 <p>Attaches one or more EC2 instances to the specified Auto Scaling group.</p><p>When you attach instances, Amazon EC2 Auto Scaling increases the desired capacity of the group by the number of instances being attached. If the number of instances being attached plus the desired capacity of the group exceeds the maximum size of the group, the operation fails.</p><p>If there is a Classic Load Balancer attached to your Auto Scaling group, the instances are also registered with the load balancer. If there are target groups attached to your Auto Scaling group, the instances are also registered with the target groups.</p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/attach-instance-asg.html">Attach EC2 instances to your Auto Scaling group</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the AttachInstances service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`, `AWSAutoScalingErrorServiceLinkedRoleFailure`.
 
 @see AWSAutoScalingAttachInstancesQuery
 */
- (void)attachInstances:(AWSAutoScalingAttachInstancesQuery *)request completionHandler:(void (^ _Nullable)(NSError * _Nullable error))completionHandler;

/**
 <p>Attaches one or more target groups to the specified Auto Scaling group.</p><p>This operation is used with the following load balancer types: </p><ul><li><p> Application Load Balancer - Operates at the application layer (layer 7) and supports HTTP and HTTPS. </p></li><li><p> Network Load Balancer - Operates at the transport layer (layer 4) and supports TCP, TLS, and UDP. </p></li><li><p> Gateway Load Balancer - Operates at the network layer (layer 3).</p></li></ul><p>To describe the target groups for an Auto Scaling group, call the <a>DescribeLoadBalancerTargetGroups</a> API. To detach the target group from the Auto Scaling group, call the <a>DetachLoadBalancerTargetGroups</a> API.</p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/autoscaling-load-balancer.html">Elastic Load Balancing and Amazon EC2 Auto Scaling</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>. </p>
 
 @param request A container for the necessary parameters to execute the AttachLoadBalancerTargetGroups service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingAttachLoadBalancerTargetGroupsResultType`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`, `AWSAutoScalingErrorServiceLinkedRoleFailure`.
 
 @see AWSAutoScalingAttachLoadBalancerTargetGroupsType
 @see AWSAutoScalingAttachLoadBalancerTargetGroupsResultType
 */
- (AWSTask<AWSAutoScalingAttachLoadBalancerTargetGroupsResultType *> *)attachLoadBalancerTargetGroups:(AWSAutoScalingAttachLoadBalancerTargetGroupsType *)request;

/**
 <p>Attaches one or more target groups to the specified Auto Scaling group.</p><p>This operation is used with the following load balancer types: </p><ul><li><p> Application Load Balancer - Operates at the application layer (layer 7) and supports HTTP and HTTPS. </p></li><li><p> Network Load Balancer - Operates at the transport layer (layer 4) and supports TCP, TLS, and UDP. </p></li><li><p> Gateway Load Balancer - Operates at the network layer (layer 3).</p></li></ul><p>To describe the target groups for an Auto Scaling group, call the <a>DescribeLoadBalancerTargetGroups</a> API. To detach the target group from the Auto Scaling group, call the <a>DetachLoadBalancerTargetGroups</a> API.</p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/autoscaling-load-balancer.html">Elastic Load Balancing and Amazon EC2 Auto Scaling</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>. </p>
 
 @param request A container for the necessary parameters to execute the AttachLoadBalancerTargetGroups service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`, `AWSAutoScalingErrorServiceLinkedRoleFailure`.
 
 @see AWSAutoScalingAttachLoadBalancerTargetGroupsType
 @see AWSAutoScalingAttachLoadBalancerTargetGroupsResultType
 */
- (void)attachLoadBalancerTargetGroups:(AWSAutoScalingAttachLoadBalancerTargetGroupsType *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingAttachLoadBalancerTargetGroupsResultType * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <note><p>To attach an Application Load Balancer, Network Load Balancer, or Gateway Load Balancer, use the <a>AttachLoadBalancerTargetGroups</a> API operation instead.</p></note><p>Attaches one or more Classic Load Balancers to the specified Auto Scaling group. Amazon EC2 Auto Scaling registers the running instances with these Classic Load Balancers.</p><p>To describe the load balancers for an Auto Scaling group, call the <a>DescribeLoadBalancers</a> API. To detach the load balancer from the Auto Scaling group, call the <a>DetachLoadBalancers</a> API.</p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/autoscaling-load-balancer.html">Elastic Load Balancing and Amazon EC2 Auto Scaling</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>. </p>
 
 @param request A container for the necessary parameters to execute the AttachLoadBalancers service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingAttachLoadBalancersResultType`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`, `AWSAutoScalingErrorServiceLinkedRoleFailure`.
 
 @see AWSAutoScalingAttachLoadBalancersType
 @see AWSAutoScalingAttachLoadBalancersResultType
 */
- (AWSTask<AWSAutoScalingAttachLoadBalancersResultType *> *)attachLoadBalancers:(AWSAutoScalingAttachLoadBalancersType *)request;

/**
 <note><p>To attach an Application Load Balancer, Network Load Balancer, or Gateway Load Balancer, use the <a>AttachLoadBalancerTargetGroups</a> API operation instead.</p></note><p>Attaches one or more Classic Load Balancers to the specified Auto Scaling group. Amazon EC2 Auto Scaling registers the running instances with these Classic Load Balancers.</p><p>To describe the load balancers for an Auto Scaling group, call the <a>DescribeLoadBalancers</a> API. To detach the load balancer from the Auto Scaling group, call the <a>DetachLoadBalancers</a> API.</p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/autoscaling-load-balancer.html">Elastic Load Balancing and Amazon EC2 Auto Scaling</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>. </p>
 
 @param request A container for the necessary parameters to execute the AttachLoadBalancers service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`, `AWSAutoScalingErrorServiceLinkedRoleFailure`.
 
 @see AWSAutoScalingAttachLoadBalancersType
 @see AWSAutoScalingAttachLoadBalancersResultType
 */
- (void)attachLoadBalancers:(AWSAutoScalingAttachLoadBalancersType *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingAttachLoadBalancersResultType * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Deletes one or more scheduled actions for the specified Auto Scaling group.</p>
 
 @param request A container for the necessary parameters to execute the BatchDeleteScheduledAction service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingBatchDeleteScheduledActionAnswer`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingBatchDeleteScheduledActionType
 @see AWSAutoScalingBatchDeleteScheduledActionAnswer
 */
- (AWSTask<AWSAutoScalingBatchDeleteScheduledActionAnswer *> *)batchDeleteScheduledAction:(AWSAutoScalingBatchDeleteScheduledActionType *)request;

/**
 <p>Deletes one or more scheduled actions for the specified Auto Scaling group.</p>
 
 @param request A container for the necessary parameters to execute the BatchDeleteScheduledAction service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingBatchDeleteScheduledActionType
 @see AWSAutoScalingBatchDeleteScheduledActionAnswer
 */
- (void)batchDeleteScheduledAction:(AWSAutoScalingBatchDeleteScheduledActionType *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingBatchDeleteScheduledActionAnswer * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Creates or updates one or more scheduled scaling actions for an Auto Scaling group.</p>
 
 @param request A container for the necessary parameters to execute the BatchPutScheduledUpdateGroupAction service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingBatchPutScheduledUpdateGroupActionAnswer`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorAlreadyExists`, `AWSAutoScalingErrorLimitExceeded`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingBatchPutScheduledUpdateGroupActionType
 @see AWSAutoScalingBatchPutScheduledUpdateGroupActionAnswer
 */
- (AWSTask<AWSAutoScalingBatchPutScheduledUpdateGroupActionAnswer *> *)batchPutScheduledUpdateGroupAction:(AWSAutoScalingBatchPutScheduledUpdateGroupActionType *)request;

/**
 <p>Creates or updates one or more scheduled scaling actions for an Auto Scaling group.</p>
 
 @param request A container for the necessary parameters to execute the BatchPutScheduledUpdateGroupAction service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorAlreadyExists`, `AWSAutoScalingErrorLimitExceeded`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingBatchPutScheduledUpdateGroupActionType
 @see AWSAutoScalingBatchPutScheduledUpdateGroupActionAnswer
 */
- (void)batchPutScheduledUpdateGroupAction:(AWSAutoScalingBatchPutScheduledUpdateGroupActionType *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingBatchPutScheduledUpdateGroupActionAnswer * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Cancels an instance refresh operation in progress. Cancellation does not roll back any replacements that have already been completed, but it prevents new replacements from being started. </p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/asg-instance-refresh.html">Replacing Auto Scaling instances based on an instance refresh</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the CancelInstanceRefresh service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingCancelInstanceRefreshAnswer`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorLimitExceeded`, `AWSAutoScalingErrorResourceContention`, `AWSAutoScalingErrorActiveInstanceRefreshNotFound`.
 
 @see AWSAutoScalingCancelInstanceRefreshType
 @see AWSAutoScalingCancelInstanceRefreshAnswer
 */
- (AWSTask<AWSAutoScalingCancelInstanceRefreshAnswer *> *)cancelInstanceRefresh:(AWSAutoScalingCancelInstanceRefreshType *)request;

/**
 <p>Cancels an instance refresh operation in progress. Cancellation does not roll back any replacements that have already been completed, but it prevents new replacements from being started. </p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/asg-instance-refresh.html">Replacing Auto Scaling instances based on an instance refresh</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the CancelInstanceRefresh service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorLimitExceeded`, `AWSAutoScalingErrorResourceContention`, `AWSAutoScalingErrorActiveInstanceRefreshNotFound`.
 
 @see AWSAutoScalingCancelInstanceRefreshType
 @see AWSAutoScalingCancelInstanceRefreshAnswer
 */
- (void)cancelInstanceRefresh:(AWSAutoScalingCancelInstanceRefreshType *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingCancelInstanceRefreshAnswer * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Completes the lifecycle action for the specified token or instance with the specified result.</p><p>This step is a part of the procedure for adding a lifecycle hook to an Auto Scaling group:</p><ol><li><p>(Optional) Create a Lambda function and a rule that allows CloudWatch Events to invoke your Lambda function when Amazon EC2 Auto Scaling launches or terminates instances.</p></li><li><p>(Optional) Create a notification target and an IAM role. The target can be either an Amazon SQS queue or an Amazon SNS topic. The role allows Amazon EC2 Auto Scaling to publish lifecycle notifications to the target.</p></li><li><p>Create the lifecycle hook. Specify whether the hook is used when the instances launch or terminate.</p></li><li><p>If you need more time, record the lifecycle action heartbeat to keep the instance in a pending state.</p></li><li><p><b>If you finish before the timeout period ends, complete the lifecycle action.</b></p></li></ol><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/lifecycle-hooks.html">Amazon EC2 Auto Scaling lifecycle hooks</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the CompleteLifecycleAction service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingCompleteLifecycleActionAnswer`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingCompleteLifecycleActionType
 @see AWSAutoScalingCompleteLifecycleActionAnswer
 */
- (AWSTask<AWSAutoScalingCompleteLifecycleActionAnswer *> *)completeLifecycleAction:(AWSAutoScalingCompleteLifecycleActionType *)request;

/**
 <p>Completes the lifecycle action for the specified token or instance with the specified result.</p><p>This step is a part of the procedure for adding a lifecycle hook to an Auto Scaling group:</p><ol><li><p>(Optional) Create a Lambda function and a rule that allows CloudWatch Events to invoke your Lambda function when Amazon EC2 Auto Scaling launches or terminates instances.</p></li><li><p>(Optional) Create a notification target and an IAM role. The target can be either an Amazon SQS queue or an Amazon SNS topic. The role allows Amazon EC2 Auto Scaling to publish lifecycle notifications to the target.</p></li><li><p>Create the lifecycle hook. Specify whether the hook is used when the instances launch or terminate.</p></li><li><p>If you need more time, record the lifecycle action heartbeat to keep the instance in a pending state.</p></li><li><p><b>If you finish before the timeout period ends, complete the lifecycle action.</b></p></li></ol><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/lifecycle-hooks.html">Amazon EC2 Auto Scaling lifecycle hooks</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the CompleteLifecycleAction service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingCompleteLifecycleActionType
 @see AWSAutoScalingCompleteLifecycleActionAnswer
 */
- (void)completeLifecycleAction:(AWSAutoScalingCompleteLifecycleActionType *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingCompleteLifecycleActionAnswer * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p><b>We strongly recommend using a launch template when calling this operation to ensure full functionality for Amazon EC2 Auto Scaling and Amazon EC2.</b></p><p>Creates an Auto Scaling group with the specified name and attributes. </p><p>If you exceed your maximum limit of Auto Scaling groups, the call fails. To query this limit, call the <a>DescribeAccountLimits</a> API. For information about updating this limit, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/as-account-limits.html">Amazon EC2 Auto Scaling service quotas</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p><p>For introductory exercises for creating an Auto Scaling group, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/GettingStartedTutorial.html">Getting started with Amazon EC2 Auto Scaling</a> and <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/as-register-lbs-with-asg.html">Tutorial: Set up a scaled and load-balanced application</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>. For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/AutoScalingGroup.html">Auto Scaling groups</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p><p>Every Auto Scaling group has three size parameters (<code>DesiredCapacity</code>, <code>MaxSize</code>, and <code>MinSize</code>). Usually, you set these sizes based on a specific number of instances. However, if you configure a mixed instances policy that defines weights for the instance types, you must specify these sizes with the same units that you use for weighting instances.</p>
 
 @param request A container for the necessary parameters to execute the CreateAutoScalingGroup service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will be `nil`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorAlreadyExists`, `AWSAutoScalingErrorLimitExceeded`, `AWSAutoScalingErrorResourceContention`, `AWSAutoScalingErrorServiceLinkedRoleFailure`.
 
 @see AWSAutoScalingCreateAutoScalingGroupType
 */
- (AWSTask *)createAutoScalingGroup:(AWSAutoScalingCreateAutoScalingGroupType *)request;

/**
 <p><b>We strongly recommend using a launch template when calling this operation to ensure full functionality for Amazon EC2 Auto Scaling and Amazon EC2.</b></p><p>Creates an Auto Scaling group with the specified name and attributes. </p><p>If you exceed your maximum limit of Auto Scaling groups, the call fails. To query this limit, call the <a>DescribeAccountLimits</a> API. For information about updating this limit, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/as-account-limits.html">Amazon EC2 Auto Scaling service quotas</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p><p>For introductory exercises for creating an Auto Scaling group, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/GettingStartedTutorial.html">Getting started with Amazon EC2 Auto Scaling</a> and <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/as-register-lbs-with-asg.html">Tutorial: Set up a scaled and load-balanced application</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>. For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/AutoScalingGroup.html">Auto Scaling groups</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p><p>Every Auto Scaling group has three size parameters (<code>DesiredCapacity</code>, <code>MaxSize</code>, and <code>MinSize</code>). Usually, you set these sizes based on a specific number of instances. However, if you configure a mixed instances policy that defines weights for the instance types, you must specify these sizes with the same units that you use for weighting instances.</p>
 
 @param request A container for the necessary parameters to execute the CreateAutoScalingGroup service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorAlreadyExists`, `AWSAutoScalingErrorLimitExceeded`, `AWSAutoScalingErrorResourceContention`, `AWSAutoScalingErrorServiceLinkedRoleFailure`.
 
 @see AWSAutoScalingCreateAutoScalingGroupType
 */
- (void)createAutoScalingGroup:(AWSAutoScalingCreateAutoScalingGroupType *)request completionHandler:(void (^ _Nullable)(NSError * _Nullable error))completionHandler;

/**
 <p>Creates a launch configuration.</p><p>If you exceed your maximum limit of launch configurations, the call fails. To query this limit, call the <a>DescribeAccountLimits</a> API. For information about updating this limit, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/as-account-limits.html">Amazon EC2 Auto Scaling service quotas</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/LaunchConfiguration.html">Launch configurations</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the CreateLaunchConfiguration service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will be `nil`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorAlreadyExists`, `AWSAutoScalingErrorLimitExceeded`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingCreateLaunchConfigurationType
 */
- (AWSTask *)createLaunchConfiguration:(AWSAutoScalingCreateLaunchConfigurationType *)request;

/**
 <p>Creates a launch configuration.</p><p>If you exceed your maximum limit of launch configurations, the call fails. To query this limit, call the <a>DescribeAccountLimits</a> API. For information about updating this limit, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/as-account-limits.html">Amazon EC2 Auto Scaling service quotas</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/LaunchConfiguration.html">Launch configurations</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the CreateLaunchConfiguration service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorAlreadyExists`, `AWSAutoScalingErrorLimitExceeded`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingCreateLaunchConfigurationType
 */
- (void)createLaunchConfiguration:(AWSAutoScalingCreateLaunchConfigurationType *)request completionHandler:(void (^ _Nullable)(NSError * _Nullable error))completionHandler;

/**
 <p>Creates or updates tags for the specified Auto Scaling group.</p><p>When you specify a tag with a key that already exists, the operation overwrites the previous tag definition, and you do not get an error message.</p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/autoscaling-tagging.html">Tagging Auto Scaling groups and instances</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the CreateOrUpdateTags service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will be `nil`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorLimitExceeded`, `AWSAutoScalingErrorAlreadyExists`, `AWSAutoScalingErrorResourceContention`, `AWSAutoScalingErrorResourceInUse`.
 
 @see AWSAutoScalingCreateOrUpdateTagsType
 */
- (AWSTask *)createOrUpdateTags:(AWSAutoScalingCreateOrUpdateTagsType *)request;

/**
 <p>Creates or updates tags for the specified Auto Scaling group.</p><p>When you specify a tag with a key that already exists, the operation overwrites the previous tag definition, and you do not get an error message.</p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/autoscaling-tagging.html">Tagging Auto Scaling groups and instances</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the CreateOrUpdateTags service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorLimitExceeded`, `AWSAutoScalingErrorAlreadyExists`, `AWSAutoScalingErrorResourceContention`, `AWSAutoScalingErrorResourceInUse`.
 
 @see AWSAutoScalingCreateOrUpdateTagsType
 */
- (void)createOrUpdateTags:(AWSAutoScalingCreateOrUpdateTagsType *)request completionHandler:(void (^ _Nullable)(NSError * _Nullable error))completionHandler;

/**
 <p>Deletes the specified Auto Scaling group.</p><p>If the group has instances or scaling activities in progress, you must specify the option to force the deletion in order for it to succeed.</p><p>If the group has policies, deleting the group deletes the policies, the underlying alarm actions, and any alarm that no longer has an associated action.</p><p>To remove instances from the Auto Scaling group before deleting it, call the <a>DetachInstances</a> API with the list of instances and the option to decrement the desired capacity. This ensures that Amazon EC2 Auto Scaling does not launch replacement instances.</p><p>To terminate all instances before deleting the Auto Scaling group, call the <a>UpdateAutoScalingGroup</a> API and set the minimum size and desired capacity of the Auto Scaling group to zero.</p>
 
 @param request A container for the necessary parameters to execute the DeleteAutoScalingGroup service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will be `nil`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorScalingActivityInProgress`, `AWSAutoScalingErrorResourceInUse`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDeleteAutoScalingGroupType
 */
- (AWSTask *)deleteAutoScalingGroup:(AWSAutoScalingDeleteAutoScalingGroupType *)request;

/**
 <p>Deletes the specified Auto Scaling group.</p><p>If the group has instances or scaling activities in progress, you must specify the option to force the deletion in order for it to succeed.</p><p>If the group has policies, deleting the group deletes the policies, the underlying alarm actions, and any alarm that no longer has an associated action.</p><p>To remove instances from the Auto Scaling group before deleting it, call the <a>DetachInstances</a> API with the list of instances and the option to decrement the desired capacity. This ensures that Amazon EC2 Auto Scaling does not launch replacement instances.</p><p>To terminate all instances before deleting the Auto Scaling group, call the <a>UpdateAutoScalingGroup</a> API and set the minimum size and desired capacity of the Auto Scaling group to zero.</p>
 
 @param request A container for the necessary parameters to execute the DeleteAutoScalingGroup service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorScalingActivityInProgress`, `AWSAutoScalingErrorResourceInUse`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDeleteAutoScalingGroupType
 */
- (void)deleteAutoScalingGroup:(AWSAutoScalingDeleteAutoScalingGroupType *)request completionHandler:(void (^ _Nullable)(NSError * _Nullable error))completionHandler;

/**
 <p>Deletes the specified launch configuration.</p><p>The launch configuration must not be attached to an Auto Scaling group. When this call completes, the launch configuration is no longer available for use.</p>
 
 @param request A container for the necessary parameters to execute the DeleteLaunchConfiguration service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will be `nil`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceInUse`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingLaunchConfigurationNameType
 */
- (AWSTask *)deleteLaunchConfiguration:(AWSAutoScalingLaunchConfigurationNameType *)request;

/**
 <p>Deletes the specified launch configuration.</p><p>The launch configuration must not be attached to an Auto Scaling group. When this call completes, the launch configuration is no longer available for use.</p>
 
 @param request A container for the necessary parameters to execute the DeleteLaunchConfiguration service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceInUse`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingLaunchConfigurationNameType
 */
- (void)deleteLaunchConfiguration:(AWSAutoScalingLaunchConfigurationNameType *)request completionHandler:(void (^ _Nullable)(NSError * _Nullable error))completionHandler;

/**
 <p>Deletes the specified lifecycle hook.</p><p>If there are any outstanding lifecycle actions, they are completed first (<code>ABANDON</code> for launching instances, <code>CONTINUE</code> for terminating instances).</p>
 
 @param request A container for the necessary parameters to execute the DeleteLifecycleHook service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingDeleteLifecycleHookAnswer`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDeleteLifecycleHookType
 @see AWSAutoScalingDeleteLifecycleHookAnswer
 */
- (AWSTask<AWSAutoScalingDeleteLifecycleHookAnswer *> *)deleteLifecycleHook:(AWSAutoScalingDeleteLifecycleHookType *)request;

/**
 <p>Deletes the specified lifecycle hook.</p><p>If there are any outstanding lifecycle actions, they are completed first (<code>ABANDON</code> for launching instances, <code>CONTINUE</code> for terminating instances).</p>
 
 @param request A container for the necessary parameters to execute the DeleteLifecycleHook service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDeleteLifecycleHookType
 @see AWSAutoScalingDeleteLifecycleHookAnswer
 */
- (void)deleteLifecycleHook:(AWSAutoScalingDeleteLifecycleHookType *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingDeleteLifecycleHookAnswer * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Deletes the specified notification.</p>
 
 @param request A container for the necessary parameters to execute the DeleteNotificationConfiguration service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will be `nil`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDeleteNotificationConfigurationType
 */
- (AWSTask *)deleteNotificationConfiguration:(AWSAutoScalingDeleteNotificationConfigurationType *)request;

/**
 <p>Deletes the specified notification.</p>
 
 @param request A container for the necessary parameters to execute the DeleteNotificationConfiguration service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDeleteNotificationConfigurationType
 */
- (void)deleteNotificationConfiguration:(AWSAutoScalingDeleteNotificationConfigurationType *)request completionHandler:(void (^ _Nullable)(NSError * _Nullable error))completionHandler;

/**
 <p>Deletes the specified scaling policy.</p><p>Deleting either a step scaling policy or a simple scaling policy deletes the underlying alarm action, but does not delete the alarm, even if it no longer has an associated action.</p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/deleting-scaling-policy.html">Deleting a scaling policy</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the DeletePolicy service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will be `nil`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`, `AWSAutoScalingErrorServiceLinkedRoleFailure`.
 
 @see AWSAutoScalingDeletePolicyType
 */
- (AWSTask *)deletePolicy:(AWSAutoScalingDeletePolicyType *)request;

/**
 <p>Deletes the specified scaling policy.</p><p>Deleting either a step scaling policy or a simple scaling policy deletes the underlying alarm action, but does not delete the alarm, even if it no longer has an associated action.</p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/deleting-scaling-policy.html">Deleting a scaling policy</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the DeletePolicy service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`, `AWSAutoScalingErrorServiceLinkedRoleFailure`.
 
 @see AWSAutoScalingDeletePolicyType
 */
- (void)deletePolicy:(AWSAutoScalingDeletePolicyType *)request completionHandler:(void (^ _Nullable)(NSError * _Nullable error))completionHandler;

/**
 <p>Deletes the specified scheduled action.</p>
 
 @param request A container for the necessary parameters to execute the DeleteScheduledAction service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will be `nil`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDeleteScheduledActionType
 */
- (AWSTask *)deleteScheduledAction:(AWSAutoScalingDeleteScheduledActionType *)request;

/**
 <p>Deletes the specified scheduled action.</p>
 
 @param request A container for the necessary parameters to execute the DeleteScheduledAction service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDeleteScheduledActionType
 */
- (void)deleteScheduledAction:(AWSAutoScalingDeleteScheduledActionType *)request completionHandler:(void (^ _Nullable)(NSError * _Nullable error))completionHandler;

/**
 <p>Deletes the specified tags.</p>
 
 @param request A container for the necessary parameters to execute the DeleteTags service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will be `nil`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`, `AWSAutoScalingErrorResourceInUse`.
 
 @see AWSAutoScalingDeleteTagsType
 */
- (AWSTask *)deleteTags:(AWSAutoScalingDeleteTagsType *)request;

/**
 <p>Deletes the specified tags.</p>
 
 @param request A container for the necessary parameters to execute the DeleteTags service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`, `AWSAutoScalingErrorResourceInUse`.
 
 @see AWSAutoScalingDeleteTagsType
 */
- (void)deleteTags:(AWSAutoScalingDeleteTagsType *)request completionHandler:(void (^ _Nullable)(NSError * _Nullable error))completionHandler;

/**
 <p>Deletes the warm pool for the specified Auto Scaling group.</p>
 
 @param request A container for the necessary parameters to execute the DeleteWarmPool service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingDeleteWarmPoolAnswer`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorLimitExceeded`, `AWSAutoScalingErrorResourceContention`, `AWSAutoScalingErrorScalingActivityInProgress`, `AWSAutoScalingErrorResourceInUse`.
 
 @see AWSAutoScalingDeleteWarmPoolType
 @see AWSAutoScalingDeleteWarmPoolAnswer
 */
- (AWSTask<AWSAutoScalingDeleteWarmPoolAnswer *> *)deleteWarmPool:(AWSAutoScalingDeleteWarmPoolType *)request;

/**
 <p>Deletes the warm pool for the specified Auto Scaling group.</p>
 
 @param request A container for the necessary parameters to execute the DeleteWarmPool service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorLimitExceeded`, `AWSAutoScalingErrorResourceContention`, `AWSAutoScalingErrorScalingActivityInProgress`, `AWSAutoScalingErrorResourceInUse`.
 
 @see AWSAutoScalingDeleteWarmPoolType
 @see AWSAutoScalingDeleteWarmPoolAnswer
 */
- (void)deleteWarmPool:(AWSAutoScalingDeleteWarmPoolType *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingDeleteWarmPoolAnswer * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Describes the current Amazon EC2 Auto Scaling resource quotas for your AWS account.</p><p>For information about requesting an increase, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/as-account-limits.html">Amazon EC2 Auto Scaling service quotas</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the DescribeAccountLimits service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingDescribeAccountLimitsAnswer`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSRequest
 @see AWSAutoScalingDescribeAccountLimitsAnswer
 */
- (AWSTask<AWSAutoScalingDescribeAccountLimitsAnswer *> *)describeAccountLimits:(AWSRequest *)request;

/**
 <p>Describes the current Amazon EC2 Auto Scaling resource quotas for your AWS account.</p><p>For information about requesting an increase, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/as-account-limits.html">Amazon EC2 Auto Scaling service quotas</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the DescribeAccountLimits service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSRequest
 @see AWSAutoScalingDescribeAccountLimitsAnswer
 */
- (void)describeAccountLimits:(AWSRequest *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingDescribeAccountLimitsAnswer * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Describes the available adjustment types for Amazon EC2 Auto Scaling scaling policies. These settings apply to step scaling policies and simple scaling policies; they do not apply to target tracking scaling policies.</p><p>The following adjustment types are supported:</p><ul><li><p>ChangeInCapacity</p></li><li><p>ExactCapacity</p></li><li><p>PercentChangeInCapacity</p></li></ul>
 
 @param request A container for the necessary parameters to execute the DescribeAdjustmentTypes service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingDescribeAdjustmentTypesAnswer`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSRequest
 @see AWSAutoScalingDescribeAdjustmentTypesAnswer
 */
- (AWSTask<AWSAutoScalingDescribeAdjustmentTypesAnswer *> *)describeAdjustmentTypes:(AWSRequest *)request;

/**
 <p>Describes the available adjustment types for Amazon EC2 Auto Scaling scaling policies. These settings apply to step scaling policies and simple scaling policies; they do not apply to target tracking scaling policies.</p><p>The following adjustment types are supported:</p><ul><li><p>ChangeInCapacity</p></li><li><p>ExactCapacity</p></li><li><p>PercentChangeInCapacity</p></li></ul>
 
 @param request A container for the necessary parameters to execute the DescribeAdjustmentTypes service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSRequest
 @see AWSAutoScalingDescribeAdjustmentTypesAnswer
 */
- (void)describeAdjustmentTypes:(AWSRequest *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingDescribeAdjustmentTypesAnswer * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Describes one or more Auto Scaling groups.</p>
 
 @param request A container for the necessary parameters to execute the DescribeAutoScalingGroups service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingAutoScalingGroupsType`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorInvalidNextToken`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingAutoScalingGroupNamesType
 @see AWSAutoScalingAutoScalingGroupsType
 */
- (AWSTask<AWSAutoScalingAutoScalingGroupsType *> *)describeAutoScalingGroups:(AWSAutoScalingAutoScalingGroupNamesType *)request;

/**
 <p>Describes one or more Auto Scaling groups.</p>
 
 @param request A container for the necessary parameters to execute the DescribeAutoScalingGroups service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorInvalidNextToken`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingAutoScalingGroupNamesType
 @see AWSAutoScalingAutoScalingGroupsType
 */
- (void)describeAutoScalingGroups:(AWSAutoScalingAutoScalingGroupNamesType *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingAutoScalingGroupsType * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Describes one or more Auto Scaling instances.</p>
 
 @param request A container for the necessary parameters to execute the DescribeAutoScalingInstances service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingAutoScalingInstancesType`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorInvalidNextToken`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDescribeAutoScalingInstancesType
 @see AWSAutoScalingAutoScalingInstancesType
 */
- (AWSTask<AWSAutoScalingAutoScalingInstancesType *> *)describeAutoScalingInstances:(AWSAutoScalingDescribeAutoScalingInstancesType *)request;

/**
 <p>Describes one or more Auto Scaling instances.</p>
 
 @param request A container for the necessary parameters to execute the DescribeAutoScalingInstances service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorInvalidNextToken`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDescribeAutoScalingInstancesType
 @see AWSAutoScalingAutoScalingInstancesType
 */
- (void)describeAutoScalingInstances:(AWSAutoScalingDescribeAutoScalingInstancesType *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingAutoScalingInstancesType * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Describes the notification types that are supported by Amazon EC2 Auto Scaling.</p>
 
 @param request A container for the necessary parameters to execute the DescribeAutoScalingNotificationTypes service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingDescribeAutoScalingNotificationTypesAnswer`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSRequest
 @see AWSAutoScalingDescribeAutoScalingNotificationTypesAnswer
 */
- (AWSTask<AWSAutoScalingDescribeAutoScalingNotificationTypesAnswer *> *)describeAutoScalingNotificationTypes:(AWSRequest *)request;

/**
 <p>Describes the notification types that are supported by Amazon EC2 Auto Scaling.</p>
 
 @param request A container for the necessary parameters to execute the DescribeAutoScalingNotificationTypes service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSRequest
 @see AWSAutoScalingDescribeAutoScalingNotificationTypesAnswer
 */
- (void)describeAutoScalingNotificationTypes:(AWSRequest *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingDescribeAutoScalingNotificationTypesAnswer * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Describes one or more instance refreshes.</p><p>You can determine the status of a request by looking at the <code>Status</code> parameter. The following are the possible statuses: </p><ul><li><p><code>Pending</code> - The request was created, but the operation has not started.</p></li><li><p><code>InProgress</code> - The operation is in progress.</p></li><li><p><code>Successful</code> - The operation completed successfully.</p></li><li><p><code>Failed</code> - The operation failed to complete. You can troubleshoot using the status reason and the scaling activities. </p></li><li><p><code>Cancelling</code> - An ongoing operation is being cancelled. Cancellation does not roll back any replacements that have already been completed, but it prevents new replacements from being started. </p></li><li><p><code>Cancelled</code> - The operation is cancelled. </p></li></ul><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/asg-instance-refresh.html">Replacing Auto Scaling instances based on an instance refresh</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the DescribeInstanceRefreshes service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingDescribeInstanceRefreshesAnswer`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorInvalidNextToken`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDescribeInstanceRefreshesType
 @see AWSAutoScalingDescribeInstanceRefreshesAnswer
 */
- (AWSTask<AWSAutoScalingDescribeInstanceRefreshesAnswer *> *)describeInstanceRefreshes:(AWSAutoScalingDescribeInstanceRefreshesType *)request;

/**
 <p>Describes one or more instance refreshes.</p><p>You can determine the status of a request by looking at the <code>Status</code> parameter. The following are the possible statuses: </p><ul><li><p><code>Pending</code> - The request was created, but the operation has not started.</p></li><li><p><code>InProgress</code> - The operation is in progress.</p></li><li><p><code>Successful</code> - The operation completed successfully.</p></li><li><p><code>Failed</code> - The operation failed to complete. You can troubleshoot using the status reason and the scaling activities. </p></li><li><p><code>Cancelling</code> - An ongoing operation is being cancelled. Cancellation does not roll back any replacements that have already been completed, but it prevents new replacements from being started. </p></li><li><p><code>Cancelled</code> - The operation is cancelled. </p></li></ul><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/asg-instance-refresh.html">Replacing Auto Scaling instances based on an instance refresh</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the DescribeInstanceRefreshes service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorInvalidNextToken`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDescribeInstanceRefreshesType
 @see AWSAutoScalingDescribeInstanceRefreshesAnswer
 */
- (void)describeInstanceRefreshes:(AWSAutoScalingDescribeInstanceRefreshesType *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingDescribeInstanceRefreshesAnswer * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Describes one or more launch configurations.</p>
 
 @param request A container for the necessary parameters to execute the DescribeLaunchConfigurations service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingLaunchConfigurationsType`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorInvalidNextToken`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingLaunchConfigurationNamesType
 @see AWSAutoScalingLaunchConfigurationsType
 */
- (AWSTask<AWSAutoScalingLaunchConfigurationsType *> *)describeLaunchConfigurations:(AWSAutoScalingLaunchConfigurationNamesType *)request;

/**
 <p>Describes one or more launch configurations.</p>
 
 @param request A container for the necessary parameters to execute the DescribeLaunchConfigurations service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorInvalidNextToken`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingLaunchConfigurationNamesType
 @see AWSAutoScalingLaunchConfigurationsType
 */
- (void)describeLaunchConfigurations:(AWSAutoScalingLaunchConfigurationNamesType *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingLaunchConfigurationsType * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Describes the available types of lifecycle hooks.</p><p>The following hook types are supported:</p><ul><li><p>autoscaling:EC2_INSTANCE_LAUNCHING</p></li><li><p>autoscaling:EC2_INSTANCE_TERMINATING</p></li></ul>
 
 @param request A container for the necessary parameters to execute the DescribeLifecycleHookTypes service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingDescribeLifecycleHookTypesAnswer`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSRequest
 @see AWSAutoScalingDescribeLifecycleHookTypesAnswer
 */
- (AWSTask<AWSAutoScalingDescribeLifecycleHookTypesAnswer *> *)describeLifecycleHookTypes:(AWSRequest *)request;

/**
 <p>Describes the available types of lifecycle hooks.</p><p>The following hook types are supported:</p><ul><li><p>autoscaling:EC2_INSTANCE_LAUNCHING</p></li><li><p>autoscaling:EC2_INSTANCE_TERMINATING</p></li></ul>
 
 @param request A container for the necessary parameters to execute the DescribeLifecycleHookTypes service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSRequest
 @see AWSAutoScalingDescribeLifecycleHookTypesAnswer
 */
- (void)describeLifecycleHookTypes:(AWSRequest *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingDescribeLifecycleHookTypesAnswer * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Describes the lifecycle hooks for the specified Auto Scaling group.</p>
 
 @param request A container for the necessary parameters to execute the DescribeLifecycleHooks service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingDescribeLifecycleHooksAnswer`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDescribeLifecycleHooksType
 @see AWSAutoScalingDescribeLifecycleHooksAnswer
 */
- (AWSTask<AWSAutoScalingDescribeLifecycleHooksAnswer *> *)describeLifecycleHooks:(AWSAutoScalingDescribeLifecycleHooksType *)request;

/**
 <p>Describes the lifecycle hooks for the specified Auto Scaling group.</p>
 
 @param request A container for the necessary parameters to execute the DescribeLifecycleHooks service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDescribeLifecycleHooksType
 @see AWSAutoScalingDescribeLifecycleHooksAnswer
 */
- (void)describeLifecycleHooks:(AWSAutoScalingDescribeLifecycleHooksType *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingDescribeLifecycleHooksAnswer * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Describes the target groups for the specified Auto Scaling group.</p>
 
 @param request A container for the necessary parameters to execute the DescribeLoadBalancerTargetGroups service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingDescribeLoadBalancerTargetGroupsResponse`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDescribeLoadBalancerTargetGroupsRequest
 @see AWSAutoScalingDescribeLoadBalancerTargetGroupsResponse
 */
- (AWSTask<AWSAutoScalingDescribeLoadBalancerTargetGroupsResponse *> *)describeLoadBalancerTargetGroups:(AWSAutoScalingDescribeLoadBalancerTargetGroupsRequest *)request;

/**
 <p>Describes the target groups for the specified Auto Scaling group.</p>
 
 @param request A container for the necessary parameters to execute the DescribeLoadBalancerTargetGroups service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDescribeLoadBalancerTargetGroupsRequest
 @see AWSAutoScalingDescribeLoadBalancerTargetGroupsResponse
 */
- (void)describeLoadBalancerTargetGroups:(AWSAutoScalingDescribeLoadBalancerTargetGroupsRequest *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingDescribeLoadBalancerTargetGroupsResponse * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Describes the load balancers for the specified Auto Scaling group.</p><p>This operation describes only Classic Load Balancers. If you have Application Load Balancers, Network Load Balancers, or Gateway Load Balancers, use the <a>DescribeLoadBalancerTargetGroups</a> API instead.</p>
 
 @param request A container for the necessary parameters to execute the DescribeLoadBalancers service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingDescribeLoadBalancersResponse`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDescribeLoadBalancersRequest
 @see AWSAutoScalingDescribeLoadBalancersResponse
 */
- (AWSTask<AWSAutoScalingDescribeLoadBalancersResponse *> *)describeLoadBalancers:(AWSAutoScalingDescribeLoadBalancersRequest *)request;

/**
 <p>Describes the load balancers for the specified Auto Scaling group.</p><p>This operation describes only Classic Load Balancers. If you have Application Load Balancers, Network Load Balancers, or Gateway Load Balancers, use the <a>DescribeLoadBalancerTargetGroups</a> API instead.</p>
 
 @param request A container for the necessary parameters to execute the DescribeLoadBalancers service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDescribeLoadBalancersRequest
 @see AWSAutoScalingDescribeLoadBalancersResponse
 */
- (void)describeLoadBalancers:(AWSAutoScalingDescribeLoadBalancersRequest *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingDescribeLoadBalancersResponse * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Describes the available CloudWatch metrics for Amazon EC2 Auto Scaling.</p><p>The <code>GroupStandbyInstances</code> metric is not returned by default. You must explicitly request this metric when calling the <a>EnableMetricsCollection</a> API.</p>
 
 @param request A container for the necessary parameters to execute the DescribeMetricCollectionTypes service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingDescribeMetricCollectionTypesAnswer`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSRequest
 @see AWSAutoScalingDescribeMetricCollectionTypesAnswer
 */
- (AWSTask<AWSAutoScalingDescribeMetricCollectionTypesAnswer *> *)describeMetricCollectionTypes:(AWSRequest *)request;

/**
 <p>Describes the available CloudWatch metrics for Amazon EC2 Auto Scaling.</p><p>The <code>GroupStandbyInstances</code> metric is not returned by default. You must explicitly request this metric when calling the <a>EnableMetricsCollection</a> API.</p>
 
 @param request A container for the necessary parameters to execute the DescribeMetricCollectionTypes service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSRequest
 @see AWSAutoScalingDescribeMetricCollectionTypesAnswer
 */
- (void)describeMetricCollectionTypes:(AWSRequest *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingDescribeMetricCollectionTypesAnswer * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Describes the notification actions associated with the specified Auto Scaling group.</p>
 
 @param request A container for the necessary parameters to execute the DescribeNotificationConfigurations service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingDescribeNotificationConfigurationsAnswer`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorInvalidNextToken`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDescribeNotificationConfigurationsType
 @see AWSAutoScalingDescribeNotificationConfigurationsAnswer
 */
- (AWSTask<AWSAutoScalingDescribeNotificationConfigurationsAnswer *> *)describeNotificationConfigurations:(AWSAutoScalingDescribeNotificationConfigurationsType *)request;

/**
 <p>Describes the notification actions associated with the specified Auto Scaling group.</p>
 
 @param request A container for the necessary parameters to execute the DescribeNotificationConfigurations service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorInvalidNextToken`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDescribeNotificationConfigurationsType
 @see AWSAutoScalingDescribeNotificationConfigurationsAnswer
 */
- (void)describeNotificationConfigurations:(AWSAutoScalingDescribeNotificationConfigurationsType *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingDescribeNotificationConfigurationsAnswer * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Describes the policies for the specified Auto Scaling group.</p>
 
 @param request A container for the necessary parameters to execute the DescribePolicies service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingPoliciesType`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorInvalidNextToken`, `AWSAutoScalingErrorResourceContention`, `AWSAutoScalingErrorServiceLinkedRoleFailure`.
 
 @see AWSAutoScalingDescribePoliciesType
 @see AWSAutoScalingPoliciesType
 */
- (AWSTask<AWSAutoScalingPoliciesType *> *)describePolicies:(AWSAutoScalingDescribePoliciesType *)request;

/**
 <p>Describes the policies for the specified Auto Scaling group.</p>
 
 @param request A container for the necessary parameters to execute the DescribePolicies service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorInvalidNextToken`, `AWSAutoScalingErrorResourceContention`, `AWSAutoScalingErrorServiceLinkedRoleFailure`.
 
 @see AWSAutoScalingDescribePoliciesType
 @see AWSAutoScalingPoliciesType
 */
- (void)describePolicies:(AWSAutoScalingDescribePoliciesType *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingPoliciesType * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Describes one or more scaling activities for the specified Auto Scaling group.</p><p>To view the scaling activities from the Amazon EC2 Auto Scaling console, choose the <b>Activity</b> tab of the Auto Scaling group. When scaling events occur, you see scaling activity messages in the <b>Activity history</b>. For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/as-verify-scaling-activity.html">Verifying a scaling activity for an Auto Scaling group</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the DescribeScalingActivities service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingActivitiesType`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorInvalidNextToken`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDescribeScalingActivitiesType
 @see AWSAutoScalingActivitiesType
 */
- (AWSTask<AWSAutoScalingActivitiesType *> *)describeScalingActivities:(AWSAutoScalingDescribeScalingActivitiesType *)request;

/**
 <p>Describes one or more scaling activities for the specified Auto Scaling group.</p><p>To view the scaling activities from the Amazon EC2 Auto Scaling console, choose the <b>Activity</b> tab of the Auto Scaling group. When scaling events occur, you see scaling activity messages in the <b>Activity history</b>. For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/as-verify-scaling-activity.html">Verifying a scaling activity for an Auto Scaling group</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the DescribeScalingActivities service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorInvalidNextToken`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDescribeScalingActivitiesType
 @see AWSAutoScalingActivitiesType
 */
- (void)describeScalingActivities:(AWSAutoScalingDescribeScalingActivitiesType *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingActivitiesType * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Describes the scaling process types for use with the <a>ResumeProcesses</a> and <a>SuspendProcesses</a> APIs.</p>
 
 @param request A container for the necessary parameters to execute the DescribeScalingProcessTypes service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingProcessesType`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSRequest
 @see AWSAutoScalingProcessesType
 */
- (AWSTask<AWSAutoScalingProcessesType *> *)describeScalingProcessTypes:(AWSRequest *)request;

/**
 <p>Describes the scaling process types for use with the <a>ResumeProcesses</a> and <a>SuspendProcesses</a> APIs.</p>
 
 @param request A container for the necessary parameters to execute the DescribeScalingProcessTypes service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSRequest
 @see AWSAutoScalingProcessesType
 */
- (void)describeScalingProcessTypes:(AWSRequest *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingProcessesType * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Describes the actions scheduled for your Auto Scaling group that haven't run or that have not reached their end time. To describe the actions that have already run, call the <a>DescribeScalingActivities</a> API.</p>
 
 @param request A container for the necessary parameters to execute the DescribeScheduledActions service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingScheduledActionsType`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorInvalidNextToken`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDescribeScheduledActionsType
 @see AWSAutoScalingScheduledActionsType
 */
- (AWSTask<AWSAutoScalingScheduledActionsType *> *)describeScheduledActions:(AWSAutoScalingDescribeScheduledActionsType *)request;

/**
 <p>Describes the actions scheduled for your Auto Scaling group that haven't run or that have not reached their end time. To describe the actions that have already run, call the <a>DescribeScalingActivities</a> API.</p>
 
 @param request A container for the necessary parameters to execute the DescribeScheduledActions service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorInvalidNextToken`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDescribeScheduledActionsType
 @see AWSAutoScalingScheduledActionsType
 */
- (void)describeScheduledActions:(AWSAutoScalingDescribeScheduledActionsType *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingScheduledActionsType * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Describes the specified tags.</p><p>You can use filters to limit the results. For example, you can query for the tags for a specific Auto Scaling group. You can specify multiple values for a filter. A tag must match at least one of the specified values for it to be included in the results.</p><p>You can also specify multiple filters. The result includes information for a particular tag only if it matches all the filters. If there's no match, no special message is returned.</p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/autoscaling-tagging.html">Tagging Auto Scaling groups and instances</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the DescribeTags service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingTagsType`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorInvalidNextToken`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDescribeTagsType
 @see AWSAutoScalingTagsType
 */
- (AWSTask<AWSAutoScalingTagsType *> *)describeTags:(AWSAutoScalingDescribeTagsType *)request;

/**
 <p>Describes the specified tags.</p><p>You can use filters to limit the results. For example, you can query for the tags for a specific Auto Scaling group. You can specify multiple values for a filter. A tag must match at least one of the specified values for it to be included in the results.</p><p>You can also specify multiple filters. The result includes information for a particular tag only if it matches all the filters. If there's no match, no special message is returned.</p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/autoscaling-tagging.html">Tagging Auto Scaling groups and instances</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the DescribeTags service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorInvalidNextToken`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDescribeTagsType
 @see AWSAutoScalingTagsType
 */
- (void)describeTags:(AWSAutoScalingDescribeTagsType *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingTagsType * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Describes the termination policies supported by Amazon EC2 Auto Scaling.</p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/as-instance-termination.html">Controlling which Auto Scaling instances terminate during scale in</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the DescribeTerminationPolicyTypes service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingDescribeTerminationPolicyTypesAnswer`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSRequest
 @see AWSAutoScalingDescribeTerminationPolicyTypesAnswer
 */
- (AWSTask<AWSAutoScalingDescribeTerminationPolicyTypesAnswer *> *)describeTerminationPolicyTypes:(AWSRequest *)request;

/**
 <p>Describes the termination policies supported by Amazon EC2 Auto Scaling.</p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/as-instance-termination.html">Controlling which Auto Scaling instances terminate during scale in</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the DescribeTerminationPolicyTypes service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSRequest
 @see AWSAutoScalingDescribeTerminationPolicyTypesAnswer
 */
- (void)describeTerminationPolicyTypes:(AWSRequest *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingDescribeTerminationPolicyTypesAnswer * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Describes a warm pool and its instances.</p>
 
 @param request A container for the necessary parameters to execute the DescribeWarmPool service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingDescribeWarmPoolAnswer`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorInvalidNextToken`, `AWSAutoScalingErrorLimitExceeded`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDescribeWarmPoolType
 @see AWSAutoScalingDescribeWarmPoolAnswer
 */
- (AWSTask<AWSAutoScalingDescribeWarmPoolAnswer *> *)describeWarmPool:(AWSAutoScalingDescribeWarmPoolType *)request;

/**
 <p>Describes a warm pool and its instances.</p>
 
 @param request A container for the necessary parameters to execute the DescribeWarmPool service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorInvalidNextToken`, `AWSAutoScalingErrorLimitExceeded`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDescribeWarmPoolType
 @see AWSAutoScalingDescribeWarmPoolAnswer
 */
- (void)describeWarmPool:(AWSAutoScalingDescribeWarmPoolType *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingDescribeWarmPoolAnswer * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Removes one or more instances from the specified Auto Scaling group.</p><p>After the instances are detached, you can manage them independent of the Auto Scaling group.</p><p>If you do not specify the option to decrement the desired capacity, Amazon EC2 Auto Scaling launches instances to replace the ones that are detached.</p><p>If there is a Classic Load Balancer attached to the Auto Scaling group, the instances are deregistered from the load balancer. If there are target groups attached to the Auto Scaling group, the instances are deregistered from the target groups.</p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/detach-instance-asg.html">Detach EC2 instances from your Auto Scaling group</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the DetachInstances service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingDetachInstancesAnswer`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDetachInstancesQuery
 @see AWSAutoScalingDetachInstancesAnswer
 */
- (AWSTask<AWSAutoScalingDetachInstancesAnswer *> *)detachInstances:(AWSAutoScalingDetachInstancesQuery *)request;

/**
 <p>Removes one or more instances from the specified Auto Scaling group.</p><p>After the instances are detached, you can manage them independent of the Auto Scaling group.</p><p>If you do not specify the option to decrement the desired capacity, Amazon EC2 Auto Scaling launches instances to replace the ones that are detached.</p><p>If there is a Classic Load Balancer attached to the Auto Scaling group, the instances are deregistered from the load balancer. If there are target groups attached to the Auto Scaling group, the instances are deregistered from the target groups.</p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/detach-instance-asg.html">Detach EC2 instances from your Auto Scaling group</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the DetachInstances service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDetachInstancesQuery
 @see AWSAutoScalingDetachInstancesAnswer
 */
- (void)detachInstances:(AWSAutoScalingDetachInstancesQuery *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingDetachInstancesAnswer * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Detaches one or more target groups from the specified Auto Scaling group.</p>
 
 @param request A container for the necessary parameters to execute the DetachLoadBalancerTargetGroups service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingDetachLoadBalancerTargetGroupsResultType`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDetachLoadBalancerTargetGroupsType
 @see AWSAutoScalingDetachLoadBalancerTargetGroupsResultType
 */
- (AWSTask<AWSAutoScalingDetachLoadBalancerTargetGroupsResultType *> *)detachLoadBalancerTargetGroups:(AWSAutoScalingDetachLoadBalancerTargetGroupsType *)request;

/**
 <p>Detaches one or more target groups from the specified Auto Scaling group.</p>
 
 @param request A container for the necessary parameters to execute the DetachLoadBalancerTargetGroups service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDetachLoadBalancerTargetGroupsType
 @see AWSAutoScalingDetachLoadBalancerTargetGroupsResultType
 */
- (void)detachLoadBalancerTargetGroups:(AWSAutoScalingDetachLoadBalancerTargetGroupsType *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingDetachLoadBalancerTargetGroupsResultType * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Detaches one or more Classic Load Balancers from the specified Auto Scaling group.</p><p>This operation detaches only Classic Load Balancers. If you have Application Load Balancers, Network Load Balancers, or Gateway Load Balancers, use the <a>DetachLoadBalancerTargetGroups</a> API instead.</p><p>When you detach a load balancer, it enters the <code>Removing</code> state while deregistering the instances in the group. When all instances are deregistered, then you can no longer describe the load balancer using the <a>DescribeLoadBalancers</a> API call. The instances remain running.</p>
 
 @param request A container for the necessary parameters to execute the DetachLoadBalancers service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingDetachLoadBalancersResultType`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDetachLoadBalancersType
 @see AWSAutoScalingDetachLoadBalancersResultType
 */
- (AWSTask<AWSAutoScalingDetachLoadBalancersResultType *> *)detachLoadBalancers:(AWSAutoScalingDetachLoadBalancersType *)request;

/**
 <p>Detaches one or more Classic Load Balancers from the specified Auto Scaling group.</p><p>This operation detaches only Classic Load Balancers. If you have Application Load Balancers, Network Load Balancers, or Gateway Load Balancers, use the <a>DetachLoadBalancerTargetGroups</a> API instead.</p><p>When you detach a load balancer, it enters the <code>Removing</code> state while deregistering the instances in the group. When all instances are deregistered, then you can no longer describe the load balancer using the <a>DescribeLoadBalancers</a> API call. The instances remain running.</p>
 
 @param request A container for the necessary parameters to execute the DetachLoadBalancers service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDetachLoadBalancersType
 @see AWSAutoScalingDetachLoadBalancersResultType
 */
- (void)detachLoadBalancers:(AWSAutoScalingDetachLoadBalancersType *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingDetachLoadBalancersResultType * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Disables group metrics for the specified Auto Scaling group.</p>
 
 @param request A container for the necessary parameters to execute the DisableMetricsCollection service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will be `nil`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDisableMetricsCollectionQuery
 */
- (AWSTask *)disableMetricsCollection:(AWSAutoScalingDisableMetricsCollectionQuery *)request;

/**
 <p>Disables group metrics for the specified Auto Scaling group.</p>
 
 @param request A container for the necessary parameters to execute the DisableMetricsCollection service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingDisableMetricsCollectionQuery
 */
- (void)disableMetricsCollection:(AWSAutoScalingDisableMetricsCollectionQuery *)request completionHandler:(void (^ _Nullable)(NSError * _Nullable error))completionHandler;

/**
 <p>Enables group metrics for the specified Auto Scaling group. For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/as-instance-monitoring.html">Monitoring CloudWatch metrics for your Auto Scaling groups and instances</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the EnableMetricsCollection service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will be `nil`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingEnableMetricsCollectionQuery
 */
- (AWSTask *)enableMetricsCollection:(AWSAutoScalingEnableMetricsCollectionQuery *)request;

/**
 <p>Enables group metrics for the specified Auto Scaling group. For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/as-instance-monitoring.html">Monitoring CloudWatch metrics for your Auto Scaling groups and instances</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the EnableMetricsCollection service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingEnableMetricsCollectionQuery
 */
- (void)enableMetricsCollection:(AWSAutoScalingEnableMetricsCollectionQuery *)request completionHandler:(void (^ _Nullable)(NSError * _Nullable error))completionHandler;

/**
 <p>Moves the specified instances into the standby state.</p><p>If you choose to decrement the desired capacity of the Auto Scaling group, the instances can enter standby as long as the desired capacity of the Auto Scaling group after the instances are placed into standby is equal to or greater than the minimum capacity of the group.</p><p>If you choose not to decrement the desired capacity of the Auto Scaling group, the Auto Scaling group launches new instances to replace the instances on standby.</p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/as-enter-exit-standby.html">Temporarily removing instances from your Auto Scaling group</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the EnterStandby service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingEnterStandbyAnswer`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingEnterStandbyQuery
 @see AWSAutoScalingEnterStandbyAnswer
 */
- (AWSTask<AWSAutoScalingEnterStandbyAnswer *> *)enterStandby:(AWSAutoScalingEnterStandbyQuery *)request;

/**
 <p>Moves the specified instances into the standby state.</p><p>If you choose to decrement the desired capacity of the Auto Scaling group, the instances can enter standby as long as the desired capacity of the Auto Scaling group after the instances are placed into standby is equal to or greater than the minimum capacity of the group.</p><p>If you choose not to decrement the desired capacity of the Auto Scaling group, the Auto Scaling group launches new instances to replace the instances on standby.</p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/as-enter-exit-standby.html">Temporarily removing instances from your Auto Scaling group</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the EnterStandby service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingEnterStandbyQuery
 @see AWSAutoScalingEnterStandbyAnswer
 */
- (void)enterStandby:(AWSAutoScalingEnterStandbyQuery *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingEnterStandbyAnswer * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Executes the specified policy. This can be useful for testing the design of your scaling policy.</p>
 
 @param request A container for the necessary parameters to execute the ExecutePolicy service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will be `nil`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorScalingActivityInProgress`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingExecutePolicyType
 */
- (AWSTask *)executePolicy:(AWSAutoScalingExecutePolicyType *)request;

/**
 <p>Executes the specified policy. This can be useful for testing the design of your scaling policy.</p>
 
 @param request A container for the necessary parameters to execute the ExecutePolicy service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorScalingActivityInProgress`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingExecutePolicyType
 */
- (void)executePolicy:(AWSAutoScalingExecutePolicyType *)request completionHandler:(void (^ _Nullable)(NSError * _Nullable error))completionHandler;

/**
 <p>Moves the specified instances out of the standby state.</p><p>After you put the instances back in service, the desired capacity is incremented.</p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/as-enter-exit-standby.html">Temporarily removing instances from your Auto Scaling group</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the ExitStandby service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingExitStandbyAnswer`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingExitStandbyQuery
 @see AWSAutoScalingExitStandbyAnswer
 */
- (AWSTask<AWSAutoScalingExitStandbyAnswer *> *)exitStandby:(AWSAutoScalingExitStandbyQuery *)request;

/**
 <p>Moves the specified instances out of the standby state.</p><p>After you put the instances back in service, the desired capacity is incremented.</p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/as-enter-exit-standby.html">Temporarily removing instances from your Auto Scaling group</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the ExitStandby service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingExitStandbyQuery
 @see AWSAutoScalingExitStandbyAnswer
 */
- (void)exitStandby:(AWSAutoScalingExitStandbyQuery *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingExitStandbyAnswer * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Creates or updates a lifecycle hook for the specified Auto Scaling group.</p><p>A lifecycle hook tells Amazon EC2 Auto Scaling to perform an action on an instance when the instance launches (before it is put into service) or as the instance terminates (before it is fully terminated).</p><p>This step is a part of the procedure for adding a lifecycle hook to an Auto Scaling group:</p><ol><li><p>(Optional) Create a Lambda function and a rule that allows CloudWatch Events to invoke your Lambda function when Amazon EC2 Auto Scaling launches or terminates instances.</p></li><li><p>(Optional) Create a notification target and an IAM role. The target can be either an Amazon SQS queue or an Amazon SNS topic. The role allows Amazon EC2 Auto Scaling to publish lifecycle notifications to the target.</p></li><li><p><b>Create the lifecycle hook. Specify whether the hook is used when the instances launch or terminate.</b></p></li><li><p>If you need more time, record the lifecycle action heartbeat to keep the instance in a pending state using the <a>RecordLifecycleActionHeartbeat</a> API call.</p></li><li><p>If you finish before the timeout period ends, complete the lifecycle action using the <a>CompleteLifecycleAction</a> API call.</p></li></ol><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/lifecycle-hooks.html">Amazon EC2 Auto Scaling lifecycle hooks</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p><p>If you exceed your maximum limit of lifecycle hooks, which by default is 50 per Auto Scaling group, the call fails.</p><p>You can view the lifecycle hooks for an Auto Scaling group using the <a>DescribeLifecycleHooks</a> API call. If you are no longer using a lifecycle hook, you can delete it by calling the <a>DeleteLifecycleHook</a> API.</p>
 
 @param request A container for the necessary parameters to execute the PutLifecycleHook service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingPutLifecycleHookAnswer`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorLimitExceeded`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingPutLifecycleHookType
 @see AWSAutoScalingPutLifecycleHookAnswer
 */
- (AWSTask<AWSAutoScalingPutLifecycleHookAnswer *> *)putLifecycleHook:(AWSAutoScalingPutLifecycleHookType *)request;

/**
 <p>Creates or updates a lifecycle hook for the specified Auto Scaling group.</p><p>A lifecycle hook tells Amazon EC2 Auto Scaling to perform an action on an instance when the instance launches (before it is put into service) or as the instance terminates (before it is fully terminated).</p><p>This step is a part of the procedure for adding a lifecycle hook to an Auto Scaling group:</p><ol><li><p>(Optional) Create a Lambda function and a rule that allows CloudWatch Events to invoke your Lambda function when Amazon EC2 Auto Scaling launches or terminates instances.</p></li><li><p>(Optional) Create a notification target and an IAM role. The target can be either an Amazon SQS queue or an Amazon SNS topic. The role allows Amazon EC2 Auto Scaling to publish lifecycle notifications to the target.</p></li><li><p><b>Create the lifecycle hook. Specify whether the hook is used when the instances launch or terminate.</b></p></li><li><p>If you need more time, record the lifecycle action heartbeat to keep the instance in a pending state using the <a>RecordLifecycleActionHeartbeat</a> API call.</p></li><li><p>If you finish before the timeout period ends, complete the lifecycle action using the <a>CompleteLifecycleAction</a> API call.</p></li></ol><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/lifecycle-hooks.html">Amazon EC2 Auto Scaling lifecycle hooks</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p><p>If you exceed your maximum limit of lifecycle hooks, which by default is 50 per Auto Scaling group, the call fails.</p><p>You can view the lifecycle hooks for an Auto Scaling group using the <a>DescribeLifecycleHooks</a> API call. If you are no longer using a lifecycle hook, you can delete it by calling the <a>DeleteLifecycleHook</a> API.</p>
 
 @param request A container for the necessary parameters to execute the PutLifecycleHook service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorLimitExceeded`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingPutLifecycleHookType
 @see AWSAutoScalingPutLifecycleHookAnswer
 */
- (void)putLifecycleHook:(AWSAutoScalingPutLifecycleHookType *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingPutLifecycleHookAnswer * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Configures an Auto Scaling group to send notifications when specified events take place. Subscribers to the specified topic can have messages delivered to an endpoint such as a web server or an email address.</p><p>This configuration overwrites any existing configuration.</p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/ASGettingNotifications.html">Getting Amazon SNS notifications when your Auto Scaling group scales</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p><p>If you exceed your maximum limit of SNS topics, which is 10 per Auto Scaling group, the call fails.</p>
 
 @param request A container for the necessary parameters to execute the PutNotificationConfiguration service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will be `nil`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorLimitExceeded`, `AWSAutoScalingErrorResourceContention`, `AWSAutoScalingErrorServiceLinkedRoleFailure`.
 
 @see AWSAutoScalingPutNotificationConfigurationType
 */
- (AWSTask *)putNotificationConfiguration:(AWSAutoScalingPutNotificationConfigurationType *)request;

/**
 <p>Configures an Auto Scaling group to send notifications when specified events take place. Subscribers to the specified topic can have messages delivered to an endpoint such as a web server or an email address.</p><p>This configuration overwrites any existing configuration.</p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/ASGettingNotifications.html">Getting Amazon SNS notifications when your Auto Scaling group scales</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p><p>If you exceed your maximum limit of SNS topics, which is 10 per Auto Scaling group, the call fails.</p>
 
 @param request A container for the necessary parameters to execute the PutNotificationConfiguration service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorLimitExceeded`, `AWSAutoScalingErrorResourceContention`, `AWSAutoScalingErrorServiceLinkedRoleFailure`.
 
 @see AWSAutoScalingPutNotificationConfigurationType
 */
- (void)putNotificationConfiguration:(AWSAutoScalingPutNotificationConfigurationType *)request completionHandler:(void (^ _Nullable)(NSError * _Nullable error))completionHandler;

/**
 <p>Creates or updates a scaling policy for an Auto Scaling group.</p><p>For more information about using scaling policies to scale your Auto Scaling group, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/as-scaling-target-tracking.html">Target tracking scaling policies</a> and <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/as-scaling-simple-step.html">Step and simple scaling policies</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the PutScalingPolicy service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingPolicyARNType`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorLimitExceeded`, `AWSAutoScalingErrorResourceContention`, `AWSAutoScalingErrorServiceLinkedRoleFailure`.
 
 @see AWSAutoScalingPutScalingPolicyType
 @see AWSAutoScalingPolicyARNType
 */
- (AWSTask<AWSAutoScalingPolicyARNType *> *)putScalingPolicy:(AWSAutoScalingPutScalingPolicyType *)request;

/**
 <p>Creates or updates a scaling policy for an Auto Scaling group.</p><p>For more information about using scaling policies to scale your Auto Scaling group, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/as-scaling-target-tracking.html">Target tracking scaling policies</a> and <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/as-scaling-simple-step.html">Step and simple scaling policies</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the PutScalingPolicy service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorLimitExceeded`, `AWSAutoScalingErrorResourceContention`, `AWSAutoScalingErrorServiceLinkedRoleFailure`.
 
 @see AWSAutoScalingPutScalingPolicyType
 @see AWSAutoScalingPolicyARNType
 */
- (void)putScalingPolicy:(AWSAutoScalingPutScalingPolicyType *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingPolicyARNType * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Creates or updates a scheduled scaling action for an Auto Scaling group.</p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/schedule_time.html">Scheduled scaling</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the PutScheduledUpdateGroupAction service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will be `nil`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorAlreadyExists`, `AWSAutoScalingErrorLimitExceeded`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingPutScheduledUpdateGroupActionType
 */
- (AWSTask *)putScheduledUpdateGroupAction:(AWSAutoScalingPutScheduledUpdateGroupActionType *)request;

/**
 <p>Creates or updates a scheduled scaling action for an Auto Scaling group.</p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/schedule_time.html">Scheduled scaling</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the PutScheduledUpdateGroupAction service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorAlreadyExists`, `AWSAutoScalingErrorLimitExceeded`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingPutScheduledUpdateGroupActionType
 */
- (void)putScheduledUpdateGroupAction:(AWSAutoScalingPutScheduledUpdateGroupActionType *)request completionHandler:(void (^ _Nullable)(NSError * _Nullable error))completionHandler;

/**
 <p>Adds a warm pool to the specified Auto Scaling group. A warm pool is a pool of pre-initialized EC2 instances that sits alongside the Auto Scaling group. Whenever your application needs to scale out, the Auto Scaling group can draw on the warm pool to meet its new desired capacity. For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/ec2-auto-scaling-warm-pools.html">Warm pools for Amazon EC2 Auto Scaling</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p><p>This operation must be called from the Region in which the Auto Scaling group was created. This operation cannot be called on an Auto Scaling group that has a mixed instances policy or a launch template or launch configuration that requests Spot Instances.</p><p>You can view the instances in the warm pool using the <a>DescribeWarmPool</a> API call. If you are no longer using a warm pool, you can delete it by calling the <a>DeleteWarmPool</a> API.</p>
 
 @param request A container for the necessary parameters to execute the PutWarmPool service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingPutWarmPoolAnswer`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorLimitExceeded`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingPutWarmPoolType
 @see AWSAutoScalingPutWarmPoolAnswer
 */
- (AWSTask<AWSAutoScalingPutWarmPoolAnswer *> *)putWarmPool:(AWSAutoScalingPutWarmPoolType *)request;

/**
 <p>Adds a warm pool to the specified Auto Scaling group. A warm pool is a pool of pre-initialized EC2 instances that sits alongside the Auto Scaling group. Whenever your application needs to scale out, the Auto Scaling group can draw on the warm pool to meet its new desired capacity. For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/ec2-auto-scaling-warm-pools.html">Warm pools for Amazon EC2 Auto Scaling</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p><p>This operation must be called from the Region in which the Auto Scaling group was created. This operation cannot be called on an Auto Scaling group that has a mixed instances policy or a launch template or launch configuration that requests Spot Instances.</p><p>You can view the instances in the warm pool using the <a>DescribeWarmPool</a> API call. If you are no longer using a warm pool, you can delete it by calling the <a>DeleteWarmPool</a> API.</p>
 
 @param request A container for the necessary parameters to execute the PutWarmPool service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorLimitExceeded`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingPutWarmPoolType
 @see AWSAutoScalingPutWarmPoolAnswer
 */
- (void)putWarmPool:(AWSAutoScalingPutWarmPoolType *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingPutWarmPoolAnswer * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Records a heartbeat for the lifecycle action associated with the specified token or instance. This extends the timeout by the length of time defined using the <a>PutLifecycleHook</a> API call.</p><p>This step is a part of the procedure for adding a lifecycle hook to an Auto Scaling group:</p><ol><li><p>(Optional) Create a Lambda function and a rule that allows CloudWatch Events to invoke your Lambda function when Amazon EC2 Auto Scaling launches or terminates instances.</p></li><li><p>(Optional) Create a notification target and an IAM role. The target can be either an Amazon SQS queue or an Amazon SNS topic. The role allows Amazon EC2 Auto Scaling to publish lifecycle notifications to the target.</p></li><li><p>Create the lifecycle hook. Specify whether the hook is used when the instances launch or terminate.</p></li><li><p><b>If you need more time, record the lifecycle action heartbeat to keep the instance in a pending state.</b></p></li><li><p>If you finish before the timeout period ends, complete the lifecycle action.</p></li></ol><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/lifecycle-hooks.html">Amazon EC2 Auto Scaling lifecycle hooks</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the RecordLifecycleActionHeartbeat service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingRecordLifecycleActionHeartbeatAnswer`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingRecordLifecycleActionHeartbeatType
 @see AWSAutoScalingRecordLifecycleActionHeartbeatAnswer
 */
- (AWSTask<AWSAutoScalingRecordLifecycleActionHeartbeatAnswer *> *)recordLifecycleActionHeartbeat:(AWSAutoScalingRecordLifecycleActionHeartbeatType *)request;

/**
 <p>Records a heartbeat for the lifecycle action associated with the specified token or instance. This extends the timeout by the length of time defined using the <a>PutLifecycleHook</a> API call.</p><p>This step is a part of the procedure for adding a lifecycle hook to an Auto Scaling group:</p><ol><li><p>(Optional) Create a Lambda function and a rule that allows CloudWatch Events to invoke your Lambda function when Amazon EC2 Auto Scaling launches or terminates instances.</p></li><li><p>(Optional) Create a notification target and an IAM role. The target can be either an Amazon SQS queue or an Amazon SNS topic. The role allows Amazon EC2 Auto Scaling to publish lifecycle notifications to the target.</p></li><li><p>Create the lifecycle hook. Specify whether the hook is used when the instances launch or terminate.</p></li><li><p><b>If you need more time, record the lifecycle action heartbeat to keep the instance in a pending state.</b></p></li><li><p>If you finish before the timeout period ends, complete the lifecycle action.</p></li></ol><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/lifecycle-hooks.html">Amazon EC2 Auto Scaling lifecycle hooks</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the RecordLifecycleActionHeartbeat service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingRecordLifecycleActionHeartbeatType
 @see AWSAutoScalingRecordLifecycleActionHeartbeatAnswer
 */
- (void)recordLifecycleActionHeartbeat:(AWSAutoScalingRecordLifecycleActionHeartbeatType *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingRecordLifecycleActionHeartbeatAnswer * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Resumes the specified suspended auto scaling processes, or all suspended process, for the specified Auto Scaling group.</p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/as-suspend-resume-processes.html">Suspending and resuming scaling processes</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the ResumeProcesses service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will be `nil`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceInUse`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingScalingProcessQuery
 */
- (AWSTask *)resumeProcesses:(AWSAutoScalingScalingProcessQuery *)request;

/**
 <p>Resumes the specified suspended auto scaling processes, or all suspended process, for the specified Auto Scaling group.</p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/as-suspend-resume-processes.html">Suspending and resuming scaling processes</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the ResumeProcesses service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceInUse`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingScalingProcessQuery
 */
- (void)resumeProcesses:(AWSAutoScalingScalingProcessQuery *)request completionHandler:(void (^ _Nullable)(NSError * _Nullable error))completionHandler;

/**
 <p>Sets the size of the specified Auto Scaling group.</p><p>If a scale-in activity occurs as a result of a new <code>DesiredCapacity</code> value that is lower than the current size of the group, the Auto Scaling group uses its termination policy to determine which instances to terminate. </p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/as-manual-scaling.html">Manual scaling</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the SetDesiredCapacity service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will be `nil`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorScalingActivityInProgress`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingSetDesiredCapacityType
 */
- (AWSTask *)setDesiredCapacity:(AWSAutoScalingSetDesiredCapacityType *)request;

/**
 <p>Sets the size of the specified Auto Scaling group.</p><p>If a scale-in activity occurs as a result of a new <code>DesiredCapacity</code> value that is lower than the current size of the group, the Auto Scaling group uses its termination policy to determine which instances to terminate. </p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/as-manual-scaling.html">Manual scaling</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the SetDesiredCapacity service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorScalingActivityInProgress`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingSetDesiredCapacityType
 */
- (void)setDesiredCapacity:(AWSAutoScalingSetDesiredCapacityType *)request completionHandler:(void (^ _Nullable)(NSError * _Nullable error))completionHandler;

/**
 <p>Sets the health status of the specified instance.</p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/healthcheck.html">Health checks for Auto Scaling instances</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the SetInstanceHealth service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will be `nil`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingSetInstanceHealthQuery
 */
- (AWSTask *)setInstanceHealth:(AWSAutoScalingSetInstanceHealthQuery *)request;

/**
 <p>Sets the health status of the specified instance.</p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/healthcheck.html">Health checks for Auto Scaling instances</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the SetInstanceHealth service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingSetInstanceHealthQuery
 */
- (void)setInstanceHealth:(AWSAutoScalingSetInstanceHealthQuery *)request completionHandler:(void (^ _Nullable)(NSError * _Nullable error))completionHandler;

/**
 <p>Updates the instance protection settings of the specified instances. This operation cannot be called on instances in a warm pool.</p><p>For more information about preventing instances that are part of an Auto Scaling group from terminating on scale in, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/as-instance-termination.html#instance-protection">Instance scale-in protection</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p><p>If you exceed your maximum limit of instance IDs, which is 50 per Auto Scaling group, the call fails.</p>
 
 @param request A container for the necessary parameters to execute the SetInstanceProtection service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingSetInstanceProtectionAnswer`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorLimitExceeded`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingSetInstanceProtectionQuery
 @see AWSAutoScalingSetInstanceProtectionAnswer
 */
- (AWSTask<AWSAutoScalingSetInstanceProtectionAnswer *> *)setInstanceProtection:(AWSAutoScalingSetInstanceProtectionQuery *)request;

/**
 <p>Updates the instance protection settings of the specified instances. This operation cannot be called on instances in a warm pool.</p><p>For more information about preventing instances that are part of an Auto Scaling group from terminating on scale in, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/as-instance-termination.html#instance-protection">Instance scale-in protection</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p><p>If you exceed your maximum limit of instance IDs, which is 50 per Auto Scaling group, the call fails.</p>
 
 @param request A container for the necessary parameters to execute the SetInstanceProtection service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorLimitExceeded`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingSetInstanceProtectionQuery
 @see AWSAutoScalingSetInstanceProtectionAnswer
 */
- (void)setInstanceProtection:(AWSAutoScalingSetInstanceProtectionQuery *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingSetInstanceProtectionAnswer * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Starts a new instance refresh operation, which triggers a rolling replacement of previously launched instances in the Auto Scaling group with a new group of instances.</p><p>If successful, this call creates a new instance refresh request with a unique ID that you can use to track its progress. To query its status, call the <a>DescribeInstanceRefreshes</a> API. To describe the instance refreshes that have already run, call the <a>DescribeInstanceRefreshes</a> API. To cancel an instance refresh operation in progress, use the <a>CancelInstanceRefresh</a> API. </p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/asg-instance-refresh.html">Replacing Auto Scaling instances based on an instance refresh</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the StartInstanceRefresh service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingStartInstanceRefreshAnswer`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorLimitExceeded`, `AWSAutoScalingErrorResourceContention`, `AWSAutoScalingErrorInstanceRefreshInProgress`.
 
 @see AWSAutoScalingStartInstanceRefreshType
 @see AWSAutoScalingStartInstanceRefreshAnswer
 */
- (AWSTask<AWSAutoScalingStartInstanceRefreshAnswer *> *)startInstanceRefresh:(AWSAutoScalingStartInstanceRefreshType *)request;

/**
 <p>Starts a new instance refresh operation, which triggers a rolling replacement of previously launched instances in the Auto Scaling group with a new group of instances.</p><p>If successful, this call creates a new instance refresh request with a unique ID that you can use to track its progress. To query its status, call the <a>DescribeInstanceRefreshes</a> API. To describe the instance refreshes that have already run, call the <a>DescribeInstanceRefreshes</a> API. To cancel an instance refresh operation in progress, use the <a>CancelInstanceRefresh</a> API. </p><p>For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/asg-instance-refresh.html">Replacing Auto Scaling instances based on an instance refresh</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the StartInstanceRefresh service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorLimitExceeded`, `AWSAutoScalingErrorResourceContention`, `AWSAutoScalingErrorInstanceRefreshInProgress`.
 
 @see AWSAutoScalingStartInstanceRefreshType
 @see AWSAutoScalingStartInstanceRefreshAnswer
 */
- (void)startInstanceRefresh:(AWSAutoScalingStartInstanceRefreshType *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingStartInstanceRefreshAnswer * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p>Suspends the specified auto scaling processes, or all processes, for the specified Auto Scaling group.</p><p>If you suspend either the <code>Launch</code> or <code>Terminate</code> process types, it can prevent other process types from functioning properly. For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/as-suspend-resume-processes.html">Suspending and resuming scaling processes</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p><p>To resume processes that have been suspended, call the <a>ResumeProcesses</a> API.</p>
 
 @param request A container for the necessary parameters to execute the SuspendProcesses service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will be `nil`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceInUse`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingScalingProcessQuery
 */
- (AWSTask *)suspendProcesses:(AWSAutoScalingScalingProcessQuery *)request;

/**
 <p>Suspends the specified auto scaling processes, or all processes, for the specified Auto Scaling group.</p><p>If you suspend either the <code>Launch</code> or <code>Terminate</code> process types, it can prevent other process types from functioning properly. For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/as-suspend-resume-processes.html">Suspending and resuming scaling processes</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p><p>To resume processes that have been suspended, call the <a>ResumeProcesses</a> API.</p>
 
 @param request A container for the necessary parameters to execute the SuspendProcesses service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorResourceInUse`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingScalingProcessQuery
 */
- (void)suspendProcesses:(AWSAutoScalingScalingProcessQuery *)request completionHandler:(void (^ _Nullable)(NSError * _Nullable error))completionHandler;

/**
 <p>Terminates the specified instance and optionally adjusts the desired group size. This operation cannot be called on instances in a warm pool.</p><p>This call simply makes a termination request. The instance is not terminated immediately. When an instance is terminated, the instance status changes to <code>terminated</code>. You can't connect to or start an instance after you've terminated it.</p><p>If you do not specify the option to decrement the desired capacity, Amazon EC2 Auto Scaling launches instances to replace the ones that are terminated. </p><p>By default, Amazon EC2 Auto Scaling balances instances across all Availability Zones. If you decrement the desired capacity, your Auto Scaling group can become unbalanced between Availability Zones. Amazon EC2 Auto Scaling tries to rebalance the group, and rebalancing might terminate instances in other zones. For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/auto-scaling-benefits.html#AutoScalingBehavior.InstanceUsage">Rebalancing activities</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the TerminateInstanceInAutoScalingGroup service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will contain an instance of `AWSAutoScalingActivityType`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorScalingActivityInProgress`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingTerminateInstanceInAutoScalingGroupType
 @see AWSAutoScalingActivityType
 */
- (AWSTask<AWSAutoScalingActivityType *> *)terminateInstanceInAutoScalingGroup:(AWSAutoScalingTerminateInstanceInAutoScalingGroupType *)request;

/**
 <p>Terminates the specified instance and optionally adjusts the desired group size. This operation cannot be called on instances in a warm pool.</p><p>This call simply makes a termination request. The instance is not terminated immediately. When an instance is terminated, the instance status changes to <code>terminated</code>. You can't connect to or start an instance after you've terminated it.</p><p>If you do not specify the option to decrement the desired capacity, Amazon EC2 Auto Scaling launches instances to replace the ones that are terminated. </p><p>By default, Amazon EC2 Auto Scaling balances instances across all Availability Zones. If you decrement the desired capacity, your Auto Scaling group can become unbalanced between Availability Zones. Amazon EC2 Auto Scaling tries to rebalance the group, and rebalancing might terminate instances in other zones. For more information, see <a href="https://docs.aws.amazon.com/autoscaling/ec2/userguide/auto-scaling-benefits.html#AutoScalingBehavior.InstanceUsage">Rebalancing activities</a> in the <i>Amazon EC2 Auto Scaling User Guide</i>.</p>
 
 @param request A container for the necessary parameters to execute the TerminateInstanceInAutoScalingGroup service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `response` - A response object, or `nil` if the request failed.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorScalingActivityInProgress`, `AWSAutoScalingErrorResourceContention`.
 
 @see AWSAutoScalingTerminateInstanceInAutoScalingGroupType
 @see AWSAutoScalingActivityType
 */
- (void)terminateInstanceInAutoScalingGroup:(AWSAutoScalingTerminateInstanceInAutoScalingGroupType *)request completionHandler:(void (^ _Nullable)(AWSAutoScalingActivityType * _Nullable response, NSError * _Nullable error))completionHandler;

/**
 <p><b>We strongly recommend that all Auto Scaling groups use launch templates to ensure full functionality for Amazon EC2 Auto Scaling and Amazon EC2.</b></p><p>Updates the configuration for the specified Auto Scaling group.</p><p>To update an Auto Scaling group, specify the name of the group and the parameter that you want to change. Any parameters that you don't specify are not changed by this update request. The new settings take effect on any scaling activities after this call returns. </p><p>If you associate a new launch configuration or template with an Auto Scaling group, all new instances will get the updated configuration. Existing instances continue to run with the configuration that they were originally launched with. When you update a group to specify a mixed instances policy instead of a launch configuration or template, existing instances may be replaced to match the new purchasing options that you specified in the policy. For example, if the group currently has 100% On-Demand capacity and the policy specifies 50% Spot capacity, this means that half of your instances will be gradually terminated and relaunched as Spot Instances. When replacing instances, Amazon EC2 Auto Scaling launches new instances before terminating the old ones, so that updating your group does not compromise the performance or availability of your application.</p><p>Note the following about changing <code>DesiredCapacity</code>, <code>MaxSize</code>, or <code>MinSize</code>:</p><ul><li><p>If a scale-in activity occurs as a result of a new <code>DesiredCapacity</code> value that is lower than the current size of the group, the Auto Scaling group uses its termination policy to determine which instances to terminate.</p></li><li><p>If you specify a new value for <code>MinSize</code> without specifying a value for <code>DesiredCapacity</code>, and the new <code>MinSize</code> is larger than the current size of the group, this sets the group's <code>DesiredCapacity</code> to the new <code>MinSize</code> value.</p></li><li><p>If you specify a new value for <code>MaxSize</code> without specifying a value for <code>DesiredCapacity</code>, and the new <code>MaxSize</code> is smaller than the current size of the group, this sets the group's <code>DesiredCapacity</code> to the new <code>MaxSize</code> value.</p></li></ul><p>To see which parameters have been set, call the <a>DescribeAutoScalingGroups</a> API. To view the scaling policies for an Auto Scaling group, call the <a>DescribePolicies</a> API. If the group has scaling policies, you can update them by calling the <a>PutScalingPolicy</a> API.</p>
 
 @param request A container for the necessary parameters to execute the UpdateAutoScalingGroup service method.

 @return An instance of `AWSTask`. On successful execution, `task.result` will be `nil`. On failed execution, `task.error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorScalingActivityInProgress`, `AWSAutoScalingErrorResourceContention`, `AWSAutoScalingErrorServiceLinkedRoleFailure`.
 
 @see AWSAutoScalingUpdateAutoScalingGroupType
 */
- (AWSTask *)updateAutoScalingGroup:(AWSAutoScalingUpdateAutoScalingGroupType *)request;

/**
 <p><b>We strongly recommend that all Auto Scaling groups use launch templates to ensure full functionality for Amazon EC2 Auto Scaling and Amazon EC2.</b></p><p>Updates the configuration for the specified Auto Scaling group.</p><p>To update an Auto Scaling group, specify the name of the group and the parameter that you want to change. Any parameters that you don't specify are not changed by this update request. The new settings take effect on any scaling activities after this call returns. </p><p>If you associate a new launch configuration or template with an Auto Scaling group, all new instances will get the updated configuration. Existing instances continue to run with the configuration that they were originally launched with. When you update a group to specify a mixed instances policy instead of a launch configuration or template, existing instances may be replaced to match the new purchasing options that you specified in the policy. For example, if the group currently has 100% On-Demand capacity and the policy specifies 50% Spot capacity, this means that half of your instances will be gradually terminated and relaunched as Spot Instances. When replacing instances, Amazon EC2 Auto Scaling launches new instances before terminating the old ones, so that updating your group does not compromise the performance or availability of your application.</p><p>Note the following about changing <code>DesiredCapacity</code>, <code>MaxSize</code>, or <code>MinSize</code>:</p><ul><li><p>If a scale-in activity occurs as a result of a new <code>DesiredCapacity</code> value that is lower than the current size of the group, the Auto Scaling group uses its termination policy to determine which instances to terminate.</p></li><li><p>If you specify a new value for <code>MinSize</code> without specifying a value for <code>DesiredCapacity</code>, and the new <code>MinSize</code> is larger than the current size of the group, this sets the group's <code>DesiredCapacity</code> to the new <code>MinSize</code> value.</p></li><li><p>If you specify a new value for <code>MaxSize</code> without specifying a value for <code>DesiredCapacity</code>, and the new <code>MaxSize</code> is smaller than the current size of the group, this sets the group's <code>DesiredCapacity</code> to the new <code>MaxSize</code> value.</p></li></ul><p>To see which parameters have been set, call the <a>DescribeAutoScalingGroups</a> API. To view the scaling policies for an Auto Scaling group, call the <a>DescribePolicies</a> API. If the group has scaling policies, you can update them by calling the <a>PutScalingPolicy</a> API.</p>
 
 @param request A container for the necessary parameters to execute the UpdateAutoScalingGroup service method.
 @param completionHandler The completion handler to call when the load request is complete.
                          `error` - An error object that indicates why the request failed, or `nil` if the request was successful. On failed execution, `error` may contain an `NSError` with `AWSAutoScalingErrorDomain` domain and the following error code: `AWSAutoScalingErrorScalingActivityInProgress`, `AWSAutoScalingErrorResourceContention`, `AWSAutoScalingErrorServiceLinkedRoleFailure`.
 
 @see AWSAutoScalingUpdateAutoScalingGroupType
 */
- (void)updateAutoScalingGroup:(AWSAutoScalingUpdateAutoScalingGroupType *)request completionHandler:(void (^ _Nullable)(NSError * _Nullable error))completionHandler;

@end

NS_ASSUME_NONNULL_END
