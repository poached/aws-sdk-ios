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

#import "AWSConnectService.h"
#import <AWSCore/AWSCategory.h>
#import <AWSCore/AWSNetworking.h>
#import <AWSCore/AWSSignature.h>
#import <AWSCore/AWSService.h>
#import <AWSCore/AWSURLRequestSerialization.h>
#import <AWSCore/AWSURLResponseSerialization.h>
#import <AWSCore/AWSURLRequestRetryHandler.h>
#import <AWSCore/AWSSynchronizedMutableDictionary.h>
#import "AWSConnectResources.h"

static NSString *const AWSInfoConnect = @"Connect";
NSString *const AWSConnectSDKVersion = @"2.24.0";


@interface AWSConnectResponseSerializer : AWSJSONResponseSerializer

@end

@implementation AWSConnectResponseSerializer

#pragma mark - Service errors

static NSDictionary *errorCodeDictionary = nil;
+ (void)initialize {
    errorCodeDictionary = @{
                            @"ContactFlowNotPublishedException" : @(AWSConnectErrorContactFlowNotPublished),
                            @"ContactNotFoundException" : @(AWSConnectErrorContactNotFound),
                            @"DestinationNotAllowedException" : @(AWSConnectErrorDestinationNotAllowed),
                            @"DuplicateResourceException" : @(AWSConnectErrorDuplicateResource),
                            @"InternalServiceException" : @(AWSConnectErrorInternalService),
                            @"InvalidContactFlowException" : @(AWSConnectErrorInvalidContactFlow),
                            @"InvalidParameterException" : @(AWSConnectErrorInvalidParameter),
                            @"InvalidRequestException" : @(AWSConnectErrorInvalidRequest),
                            @"LimitExceededException" : @(AWSConnectErrorLimitExceeded),
                            @"OutboundContactNotPermittedException" : @(AWSConnectErrorOutboundContactNotPermitted),
                            @"ResourceConflictException" : @(AWSConnectErrorResourceConflict),
                            @"ResourceInUseException" : @(AWSConnectErrorResourceInUse),
                            @"ResourceNotFoundException" : @(AWSConnectErrorResourceNotFound),
                            @"ServiceQuotaExceededException" : @(AWSConnectErrorServiceQuotaExceeded),
                            @"ThrottlingException" : @(AWSConnectErrorThrottling),
                            @"UserNotFoundException" : @(AWSConnectErrorUserNotFound),
                            };
}

#pragma mark -

- (id)responseObjectForResponse:(NSHTTPURLResponse *)response
                originalRequest:(NSURLRequest *)originalRequest
                 currentRequest:(NSURLRequest *)currentRequest
                           data:(id)data
                          error:(NSError *__autoreleasing *)error {
    id responseObject = [super responseObjectForResponse:response
                                         originalRequest:originalRequest
                                          currentRequest:currentRequest
                                                    data:data
                                                   error:error];
    if (!*error && [responseObject isKindOfClass:[NSDictionary class]]) {
    	NSString *errorTypeString = [[response allHeaderFields] objectForKey:@"x-amzn-ErrorType"];
        NSString *errorTypeHeader = [[errorTypeString componentsSeparatedByString:@":"] firstObject];

        if ([errorTypeString length] > 0 && errorTypeHeader) {
            if (errorCodeDictionary[errorTypeHeader]) {
                if (error) {
                    NSDictionary *userInfo = @{NSLocalizedDescriptionKey : [responseObject objectForKey:@"message"]?[responseObject objectForKey:@"message"]:[NSNull null], NSLocalizedFailureReasonErrorKey: errorTypeString};
                    *error = [NSError errorWithDomain:AWSConnectErrorDomain
                                                 code:[[errorCodeDictionary objectForKey:errorTypeHeader] integerValue]
                                             userInfo:userInfo];
                }
                return responseObject;
            } else if (errorTypeHeader) {
                if (error) {
                    NSDictionary *userInfo = @{NSLocalizedDescriptionKey : [responseObject objectForKey:@"message"]?[responseObject objectForKey:@"message"]:[NSNull null], NSLocalizedFailureReasonErrorKey: errorTypeString};
                    *error = [NSError errorWithDomain:AWSConnectErrorDomain
                                                 code:AWSConnectErrorUnknown
                                             userInfo:userInfo];
                }
                return responseObject;
            }
        }
    }

    if (!*error && response.statusCode/100 != 2) {
        *error = [NSError errorWithDomain:AWSConnectErrorDomain
                                     code:AWSConnectErrorUnknown
                                 userInfo:nil];
    }

    if (!*error && [responseObject isKindOfClass:[NSDictionary class]]) {
        if (self.outputClass) {
            responseObject = [AWSMTLJSONAdapter modelOfClass:self.outputClass
                                          fromJSONDictionary:responseObject
                                                       error:error];
        }
    }
	
    return responseObject;
}

@end

@interface AWSConnectRequestRetryHandler : AWSURLRequestRetryHandler

@end

@implementation AWSConnectRequestRetryHandler

@end

@interface AWSRequest()

@property (nonatomic, strong) AWSNetworkingRequest *internalRequest;

@end

@interface AWSConnect()

@property (nonatomic, strong) AWSNetworking *networking;
@property (nonatomic, strong) AWSServiceConfiguration *configuration;

@end

@interface AWSServiceConfiguration()

@property (nonatomic, strong) AWSEndpoint *endpoint;

@end

@interface AWSEndpoint()

- (void) setRegion:(AWSRegionType)regionType service:(AWSServiceType)serviceType;

@end

@implementation AWSConnect

+ (void)initialize {
    [super initialize];

    if (![AWSiOSSDKVersion isEqualToString:AWSConnectSDKVersion]) {
        @throw [NSException exceptionWithName:NSInternalInconsistencyException
                                       reason:[NSString stringWithFormat:@"AWSCore and AWSConnect versions need to match. Check your SDK installation. AWSCore: %@ AWSConnect: %@", AWSiOSSDKVersion, AWSConnectSDKVersion]
                                     userInfo:nil];
    }
}

#pragma mark - Setup

static AWSSynchronizedMutableDictionary *_serviceClients = nil;

+ (instancetype)defaultConnect {
    static AWSConnect *_defaultConnect = nil;
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        AWSServiceConfiguration *serviceConfiguration = nil;
        AWSServiceInfo *serviceInfo = [[AWSInfo defaultAWSInfo] defaultServiceInfo:AWSInfoConnect];
        if (serviceInfo) {
            serviceConfiguration = [[AWSServiceConfiguration alloc] initWithRegion:serviceInfo.region
                                                               credentialsProvider:serviceInfo.cognitoCredentialsProvider];
        }

        if (!serviceConfiguration) {
            serviceConfiguration = [AWSServiceManager defaultServiceManager].defaultServiceConfiguration;
        }

        if (!serviceConfiguration) {
            @throw [NSException exceptionWithName:NSInternalInconsistencyException
                                           reason:@"The service configuration is `nil`. You need to configure `awsconfiguration.json`, `Info.plist` or set `defaultServiceConfiguration` before using this method."
                                         userInfo:nil];
        }
        _defaultConnect = [[AWSConnect alloc] initWithConfiguration:serviceConfiguration];
    });

    return _defaultConnect;
}

+ (void)registerConnectWithConfiguration:(AWSServiceConfiguration *)configuration forKey:(NSString *)key {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        _serviceClients = [AWSSynchronizedMutableDictionary new];
    });
    [_serviceClients setObject:[[AWSConnect alloc] initWithConfiguration:configuration]
                        forKey:key];
}

+ (instancetype)ConnectForKey:(NSString *)key {
    @synchronized(self) {
        AWSConnect *serviceClient = [_serviceClients objectForKey:key];
        if (serviceClient) {
            return serviceClient;
        }

        AWSServiceInfo *serviceInfo = [[AWSInfo defaultAWSInfo] serviceInfo:AWSInfoConnect
                                                                     forKey:key];
        if (serviceInfo) {
            AWSServiceConfiguration *serviceConfiguration = [[AWSServiceConfiguration alloc] initWithRegion:serviceInfo.region
                                                                                        credentialsProvider:serviceInfo.cognitoCredentialsProvider];
            [AWSConnect registerConnectWithConfiguration:serviceConfiguration
                                                                forKey:key];
        }

        return [_serviceClients objectForKey:key];
    }
}

+ (void)removeConnectForKey:(NSString *)key {
    [_serviceClients removeObjectForKey:key];
}

- (instancetype)init {
    @throw [NSException exceptionWithName:NSInternalInconsistencyException
                                   reason:@"`- init` is not a valid initializer. Use `+ defaultConnect` or `+ ConnectForKey:` instead."
                                 userInfo:nil];
    return nil;
}

#pragma mark -

- (instancetype)initWithConfiguration:(AWSServiceConfiguration *)configuration {
    if (self = [super init]) {
        _configuration = [configuration copy];
       	
        if(!configuration.endpoint){
            _configuration.endpoint = [[AWSEndpoint alloc] initWithRegion:_configuration.regionType
                                                              service:AWSServiceConnect
                                                         useUnsafeURL:NO];
        }else{
            [_configuration.endpoint setRegion:_configuration.regionType
                                      service:AWSServiceConnect];
        }
       	
        AWSSignatureV4Signer *signer = [[AWSSignatureV4Signer alloc] initWithCredentialsProvider:_configuration.credentialsProvider
                                                                                        endpoint:_configuration.endpoint];
        AWSNetworkingRequestInterceptor *baseInterceptor = [[AWSNetworkingRequestInterceptor alloc] initWithUserAgent:_configuration.userAgent];
        _configuration.requestInterceptors = @[baseInterceptor, signer];

        _configuration.baseURL = _configuration.endpoint.URL;
        _configuration.retryHandler = [[AWSConnectRequestRetryHandler alloc] initWithMaximumRetryCount:_configuration.maxRetryCount];
        _configuration.headers = @{@"Content-Type" : @"application/x-amz-json-1.1"}; 
		
        _networking = [[AWSNetworking alloc] initWithConfiguration:_configuration];
    }
    
    return self;
}

- (AWSTask *)invokeRequest:(AWSRequest *)request
               HTTPMethod:(AWSHTTPMethod)HTTPMethod
                URLString:(NSString *) URLString
             targetPrefix:(NSString *)targetPrefix
            operationName:(NSString *)operationName
              outputClass:(Class)outputClass {
    
    @autoreleasepool {
        if (!request) {
            request = [AWSRequest new];
        }

        AWSNetworkingRequest *networkingRequest = request.internalRequest;
        if (request) {
            networkingRequest.parameters = [[AWSMTLJSONAdapter JSONDictionaryFromModel:request] aws_removeNullValues];
        } else {
            networkingRequest.parameters = @{};
        }

        networkingRequest.HTTPMethod = HTTPMethod;
        networkingRequest.requestSerializer = [[AWSJSONRequestSerializer alloc] initWithJSONDefinition:[[AWSConnectResources sharedInstance] JSONObject]
                                                                                                   actionName:operationName];
        networkingRequest.responseSerializer = [[AWSConnectResponseSerializer alloc] initWithJSONDefinition:[[AWSConnectResources sharedInstance] JSONObject]
                                                                                             actionName:operationName
                                                                                            outputClass:outputClass];
        
        return [self.networking sendRequest:networkingRequest];
    }
}

#pragma mark - Service method

- (AWSTask *)associateApprovedOrigin:(AWSConnectAssociateApprovedOriginRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPUT
                     URLString:@"/instance/{InstanceId}/approved-origin"
                  targetPrefix:@""
                 operationName:@"AssociateApprovedOrigin"
                   outputClass:nil];
}

- (void)associateApprovedOrigin:(AWSConnectAssociateApprovedOriginRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self associateApprovedOrigin:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectAssociateInstanceStorageConfigResponse *> *)associateInstanceStorageConfig:(AWSConnectAssociateInstanceStorageConfigRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPUT
                     URLString:@"/instance/{InstanceId}/storage-config"
                  targetPrefix:@""
                 operationName:@"AssociateInstanceStorageConfig"
                   outputClass:[AWSConnectAssociateInstanceStorageConfigResponse class]];
}

- (void)associateInstanceStorageConfig:(AWSConnectAssociateInstanceStorageConfigRequest *)request
     completionHandler:(void (^)(AWSConnectAssociateInstanceStorageConfigResponse *response, NSError *error))completionHandler {
    [[self associateInstanceStorageConfig:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectAssociateInstanceStorageConfigResponse *> * _Nonnull task) {
        AWSConnectAssociateInstanceStorageConfigResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask *)associateLambdaFunction:(AWSConnectAssociateLambdaFunctionRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPUT
                     URLString:@"/instance/{InstanceId}/lambda-function"
                  targetPrefix:@""
                 operationName:@"AssociateLambdaFunction"
                   outputClass:nil];
}

- (void)associateLambdaFunction:(AWSConnectAssociateLambdaFunctionRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self associateLambdaFunction:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)associateLexBot:(AWSConnectAssociateLexBotRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPUT
                     URLString:@"/instance/{InstanceId}/lex-bot"
                  targetPrefix:@""
                 operationName:@"AssociateLexBot"
                   outputClass:nil];
}

- (void)associateLexBot:(AWSConnectAssociateLexBotRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self associateLexBot:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)associateQueueQuickConnects:(AWSConnectAssociateQueueQuickConnectsRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/queues/{InstanceId}/{QueueId}/associate-quick-connects"
                  targetPrefix:@""
                 operationName:@"AssociateQueueQuickConnects"
                   outputClass:nil];
}

- (void)associateQueueQuickConnects:(AWSConnectAssociateQueueQuickConnectsRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self associateQueueQuickConnects:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)associateRoutingProfileQueues:(AWSConnectAssociateRoutingProfileQueuesRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/routing-profiles/{InstanceId}/{RoutingProfileId}/associate-queues"
                  targetPrefix:@""
                 operationName:@"AssociateRoutingProfileQueues"
                   outputClass:nil];
}

- (void)associateRoutingProfileQueues:(AWSConnectAssociateRoutingProfileQueuesRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self associateRoutingProfileQueues:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectAssociateSecurityKeyResponse *> *)associateSecurityKey:(AWSConnectAssociateSecurityKeyRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPUT
                     URLString:@"/instance/{InstanceId}/security-key"
                  targetPrefix:@""
                 operationName:@"AssociateSecurityKey"
                   outputClass:[AWSConnectAssociateSecurityKeyResponse class]];
}

- (void)associateSecurityKey:(AWSConnectAssociateSecurityKeyRequest *)request
     completionHandler:(void (^)(AWSConnectAssociateSecurityKeyResponse *response, NSError *error))completionHandler {
    [[self associateSecurityKey:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectAssociateSecurityKeyResponse *> * _Nonnull task) {
        AWSConnectAssociateSecurityKeyResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectCreateContactFlowResponse *> *)createContactFlow:(AWSConnectCreateContactFlowRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPUT
                     URLString:@"/contact-flows/{InstanceId}"
                  targetPrefix:@""
                 operationName:@"CreateContactFlow"
                   outputClass:[AWSConnectCreateContactFlowResponse class]];
}

- (void)createContactFlow:(AWSConnectCreateContactFlowRequest *)request
     completionHandler:(void (^)(AWSConnectCreateContactFlowResponse *response, NSError *error))completionHandler {
    [[self createContactFlow:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectCreateContactFlowResponse *> * _Nonnull task) {
        AWSConnectCreateContactFlowResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectCreateInstanceResponse *> *)createInstance:(AWSConnectCreateInstanceRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPUT
                     URLString:@"/instance"
                  targetPrefix:@""
                 operationName:@"CreateInstance"
                   outputClass:[AWSConnectCreateInstanceResponse class]];
}

- (void)createInstance:(AWSConnectCreateInstanceRequest *)request
     completionHandler:(void (^)(AWSConnectCreateInstanceResponse *response, NSError *error))completionHandler {
    [[self createInstance:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectCreateInstanceResponse *> * _Nonnull task) {
        AWSConnectCreateInstanceResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectCreateIntegrationAssociationResponse *> *)createIntegrationAssociation:(AWSConnectCreateIntegrationAssociationRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPUT
                     URLString:@"/instance/{InstanceId}/integration-associations"
                  targetPrefix:@""
                 operationName:@"CreateIntegrationAssociation"
                   outputClass:[AWSConnectCreateIntegrationAssociationResponse class]];
}

- (void)createIntegrationAssociation:(AWSConnectCreateIntegrationAssociationRequest *)request
     completionHandler:(void (^)(AWSConnectCreateIntegrationAssociationResponse *response, NSError *error))completionHandler {
    [[self createIntegrationAssociation:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectCreateIntegrationAssociationResponse *> * _Nonnull task) {
        AWSConnectCreateIntegrationAssociationResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectCreateQueueResponse *> *)createQueue:(AWSConnectCreateQueueRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPUT
                     URLString:@"/queues/{InstanceId}"
                  targetPrefix:@""
                 operationName:@"CreateQueue"
                   outputClass:[AWSConnectCreateQueueResponse class]];
}

- (void)createQueue:(AWSConnectCreateQueueRequest *)request
     completionHandler:(void (^)(AWSConnectCreateQueueResponse *response, NSError *error))completionHandler {
    [[self createQueue:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectCreateQueueResponse *> * _Nonnull task) {
        AWSConnectCreateQueueResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectCreateQuickConnectResponse *> *)createQuickConnect:(AWSConnectCreateQuickConnectRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPUT
                     URLString:@"/quick-connects/{InstanceId}"
                  targetPrefix:@""
                 operationName:@"CreateQuickConnect"
                   outputClass:[AWSConnectCreateQuickConnectResponse class]];
}

- (void)createQuickConnect:(AWSConnectCreateQuickConnectRequest *)request
     completionHandler:(void (^)(AWSConnectCreateQuickConnectResponse *response, NSError *error))completionHandler {
    [[self createQuickConnect:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectCreateQuickConnectResponse *> * _Nonnull task) {
        AWSConnectCreateQuickConnectResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectCreateRoutingProfileResponse *> *)createRoutingProfile:(AWSConnectCreateRoutingProfileRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPUT
                     URLString:@"/routing-profiles/{InstanceId}"
                  targetPrefix:@""
                 operationName:@"CreateRoutingProfile"
                   outputClass:[AWSConnectCreateRoutingProfileResponse class]];
}

- (void)createRoutingProfile:(AWSConnectCreateRoutingProfileRequest *)request
     completionHandler:(void (^)(AWSConnectCreateRoutingProfileResponse *response, NSError *error))completionHandler {
    [[self createRoutingProfile:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectCreateRoutingProfileResponse *> * _Nonnull task) {
        AWSConnectCreateRoutingProfileResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectCreateUseCaseResponse *> *)createUseCase:(AWSConnectCreateUseCaseRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPUT
                     URLString:@"/instance/{InstanceId}/integration-associations/{IntegrationAssociationId}/use-cases"
                  targetPrefix:@""
                 operationName:@"CreateUseCase"
                   outputClass:[AWSConnectCreateUseCaseResponse class]];
}

- (void)createUseCase:(AWSConnectCreateUseCaseRequest *)request
     completionHandler:(void (^)(AWSConnectCreateUseCaseResponse *response, NSError *error))completionHandler {
    [[self createUseCase:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectCreateUseCaseResponse *> * _Nonnull task) {
        AWSConnectCreateUseCaseResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectCreateUserResponse *> *)createUser:(AWSConnectCreateUserRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPUT
                     URLString:@"/users/{InstanceId}"
                  targetPrefix:@""
                 operationName:@"CreateUser"
                   outputClass:[AWSConnectCreateUserResponse class]];
}

- (void)createUser:(AWSConnectCreateUserRequest *)request
     completionHandler:(void (^)(AWSConnectCreateUserResponse *response, NSError *error))completionHandler {
    [[self createUser:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectCreateUserResponse *> * _Nonnull task) {
        AWSConnectCreateUserResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectCreateUserHierarchyGroupResponse *> *)createUserHierarchyGroup:(AWSConnectCreateUserHierarchyGroupRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPUT
                     URLString:@"/user-hierarchy-groups/{InstanceId}"
                  targetPrefix:@""
                 operationName:@"CreateUserHierarchyGroup"
                   outputClass:[AWSConnectCreateUserHierarchyGroupResponse class]];
}

- (void)createUserHierarchyGroup:(AWSConnectCreateUserHierarchyGroupRequest *)request
     completionHandler:(void (^)(AWSConnectCreateUserHierarchyGroupResponse *response, NSError *error))completionHandler {
    [[self createUserHierarchyGroup:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectCreateUserHierarchyGroupResponse *> * _Nonnull task) {
        AWSConnectCreateUserHierarchyGroupResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask *)deleteInstance:(AWSConnectDeleteInstanceRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodDELETE
                     URLString:@"/instance/{InstanceId}"
                  targetPrefix:@""
                 operationName:@"DeleteInstance"
                   outputClass:nil];
}

- (void)deleteInstance:(AWSConnectDeleteInstanceRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self deleteInstance:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)deleteIntegrationAssociation:(AWSConnectDeleteIntegrationAssociationRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodDELETE
                     URLString:@"/instance/{InstanceId}/integration-associations/{IntegrationAssociationId}"
                  targetPrefix:@""
                 operationName:@"DeleteIntegrationAssociation"
                   outputClass:nil];
}

- (void)deleteIntegrationAssociation:(AWSConnectDeleteIntegrationAssociationRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self deleteIntegrationAssociation:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)deleteQuickConnect:(AWSConnectDeleteQuickConnectRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodDELETE
                     URLString:@"/quick-connects/{InstanceId}/{QuickConnectId}"
                  targetPrefix:@""
                 operationName:@"DeleteQuickConnect"
                   outputClass:nil];
}

- (void)deleteQuickConnect:(AWSConnectDeleteQuickConnectRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self deleteQuickConnect:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)deleteUseCase:(AWSConnectDeleteUseCaseRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodDELETE
                     URLString:@"/instance/{InstanceId}/integration-associations/{IntegrationAssociationId}/use-cases/{UseCaseId}"
                  targetPrefix:@""
                 operationName:@"DeleteUseCase"
                   outputClass:nil];
}

- (void)deleteUseCase:(AWSConnectDeleteUseCaseRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self deleteUseCase:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)deleteUser:(AWSConnectDeleteUserRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodDELETE
                     URLString:@"/users/{InstanceId}/{UserId}"
                  targetPrefix:@""
                 operationName:@"DeleteUser"
                   outputClass:nil];
}

- (void)deleteUser:(AWSConnectDeleteUserRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self deleteUser:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)deleteUserHierarchyGroup:(AWSConnectDeleteUserHierarchyGroupRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodDELETE
                     URLString:@"/user-hierarchy-groups/{InstanceId}/{HierarchyGroupId}"
                  targetPrefix:@""
                 operationName:@"DeleteUserHierarchyGroup"
                   outputClass:nil];
}

- (void)deleteUserHierarchyGroup:(AWSConnectDeleteUserHierarchyGroupRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self deleteUserHierarchyGroup:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectDescribeContactFlowResponse *> *)describeContactFlow:(AWSConnectDescribeContactFlowRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/contact-flows/{InstanceId}/{ContactFlowId}"
                  targetPrefix:@""
                 operationName:@"DescribeContactFlow"
                   outputClass:[AWSConnectDescribeContactFlowResponse class]];
}

- (void)describeContactFlow:(AWSConnectDescribeContactFlowRequest *)request
     completionHandler:(void (^)(AWSConnectDescribeContactFlowResponse *response, NSError *error))completionHandler {
    [[self describeContactFlow:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectDescribeContactFlowResponse *> * _Nonnull task) {
        AWSConnectDescribeContactFlowResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectDescribeHoursOfOperationResponse *> *)describeHoursOfOperation:(AWSConnectDescribeHoursOfOperationRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/hours-of-operations/{InstanceId}/{HoursOfOperationId}"
                  targetPrefix:@""
                 operationName:@"DescribeHoursOfOperation"
                   outputClass:[AWSConnectDescribeHoursOfOperationResponse class]];
}

- (void)describeHoursOfOperation:(AWSConnectDescribeHoursOfOperationRequest *)request
     completionHandler:(void (^)(AWSConnectDescribeHoursOfOperationResponse *response, NSError *error))completionHandler {
    [[self describeHoursOfOperation:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectDescribeHoursOfOperationResponse *> * _Nonnull task) {
        AWSConnectDescribeHoursOfOperationResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectDescribeInstanceResponse *> *)describeInstance:(AWSConnectDescribeInstanceRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/instance/{InstanceId}"
                  targetPrefix:@""
                 operationName:@"DescribeInstance"
                   outputClass:[AWSConnectDescribeInstanceResponse class]];
}

- (void)describeInstance:(AWSConnectDescribeInstanceRequest *)request
     completionHandler:(void (^)(AWSConnectDescribeInstanceResponse *response, NSError *error))completionHandler {
    [[self describeInstance:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectDescribeInstanceResponse *> * _Nonnull task) {
        AWSConnectDescribeInstanceResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectDescribeInstanceAttributeResponse *> *)describeInstanceAttribute:(AWSConnectDescribeInstanceAttributeRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/instance/{InstanceId}/attribute/{AttributeType}"
                  targetPrefix:@""
                 operationName:@"DescribeInstanceAttribute"
                   outputClass:[AWSConnectDescribeInstanceAttributeResponse class]];
}

- (void)describeInstanceAttribute:(AWSConnectDescribeInstanceAttributeRequest *)request
     completionHandler:(void (^)(AWSConnectDescribeInstanceAttributeResponse *response, NSError *error))completionHandler {
    [[self describeInstanceAttribute:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectDescribeInstanceAttributeResponse *> * _Nonnull task) {
        AWSConnectDescribeInstanceAttributeResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectDescribeInstanceStorageConfigResponse *> *)describeInstanceStorageConfig:(AWSConnectDescribeInstanceStorageConfigRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/instance/{InstanceId}/storage-config/{AssociationId}"
                  targetPrefix:@""
                 operationName:@"DescribeInstanceStorageConfig"
                   outputClass:[AWSConnectDescribeInstanceStorageConfigResponse class]];
}

- (void)describeInstanceStorageConfig:(AWSConnectDescribeInstanceStorageConfigRequest *)request
     completionHandler:(void (^)(AWSConnectDescribeInstanceStorageConfigResponse *response, NSError *error))completionHandler {
    [[self describeInstanceStorageConfig:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectDescribeInstanceStorageConfigResponse *> * _Nonnull task) {
        AWSConnectDescribeInstanceStorageConfigResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectDescribeQueueResponse *> *)describeQueue:(AWSConnectDescribeQueueRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/queues/{InstanceId}/{QueueId}"
                  targetPrefix:@""
                 operationName:@"DescribeQueue"
                   outputClass:[AWSConnectDescribeQueueResponse class]];
}

- (void)describeQueue:(AWSConnectDescribeQueueRequest *)request
     completionHandler:(void (^)(AWSConnectDescribeQueueResponse *response, NSError *error))completionHandler {
    [[self describeQueue:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectDescribeQueueResponse *> * _Nonnull task) {
        AWSConnectDescribeQueueResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectDescribeQuickConnectResponse *> *)describeQuickConnect:(AWSConnectDescribeQuickConnectRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/quick-connects/{InstanceId}/{QuickConnectId}"
                  targetPrefix:@""
                 operationName:@"DescribeQuickConnect"
                   outputClass:[AWSConnectDescribeQuickConnectResponse class]];
}

- (void)describeQuickConnect:(AWSConnectDescribeQuickConnectRequest *)request
     completionHandler:(void (^)(AWSConnectDescribeQuickConnectResponse *response, NSError *error))completionHandler {
    [[self describeQuickConnect:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectDescribeQuickConnectResponse *> * _Nonnull task) {
        AWSConnectDescribeQuickConnectResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectDescribeRoutingProfileResponse *> *)describeRoutingProfile:(AWSConnectDescribeRoutingProfileRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/routing-profiles/{InstanceId}/{RoutingProfileId}"
                  targetPrefix:@""
                 operationName:@"DescribeRoutingProfile"
                   outputClass:[AWSConnectDescribeRoutingProfileResponse class]];
}

- (void)describeRoutingProfile:(AWSConnectDescribeRoutingProfileRequest *)request
     completionHandler:(void (^)(AWSConnectDescribeRoutingProfileResponse *response, NSError *error))completionHandler {
    [[self describeRoutingProfile:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectDescribeRoutingProfileResponse *> * _Nonnull task) {
        AWSConnectDescribeRoutingProfileResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectDescribeUserResponse *> *)describeUser:(AWSConnectDescribeUserRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/users/{InstanceId}/{UserId}"
                  targetPrefix:@""
                 operationName:@"DescribeUser"
                   outputClass:[AWSConnectDescribeUserResponse class]];
}

- (void)describeUser:(AWSConnectDescribeUserRequest *)request
     completionHandler:(void (^)(AWSConnectDescribeUserResponse *response, NSError *error))completionHandler {
    [[self describeUser:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectDescribeUserResponse *> * _Nonnull task) {
        AWSConnectDescribeUserResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectDescribeUserHierarchyGroupResponse *> *)describeUserHierarchyGroup:(AWSConnectDescribeUserHierarchyGroupRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/user-hierarchy-groups/{InstanceId}/{HierarchyGroupId}"
                  targetPrefix:@""
                 operationName:@"DescribeUserHierarchyGroup"
                   outputClass:[AWSConnectDescribeUserHierarchyGroupResponse class]];
}

- (void)describeUserHierarchyGroup:(AWSConnectDescribeUserHierarchyGroupRequest *)request
     completionHandler:(void (^)(AWSConnectDescribeUserHierarchyGroupResponse *response, NSError *error))completionHandler {
    [[self describeUserHierarchyGroup:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectDescribeUserHierarchyGroupResponse *> * _Nonnull task) {
        AWSConnectDescribeUserHierarchyGroupResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectDescribeUserHierarchyStructureResponse *> *)describeUserHierarchyStructure:(AWSConnectDescribeUserHierarchyStructureRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/user-hierarchy-structure/{InstanceId}"
                  targetPrefix:@""
                 operationName:@"DescribeUserHierarchyStructure"
                   outputClass:[AWSConnectDescribeUserHierarchyStructureResponse class]];
}

- (void)describeUserHierarchyStructure:(AWSConnectDescribeUserHierarchyStructureRequest *)request
     completionHandler:(void (^)(AWSConnectDescribeUserHierarchyStructureResponse *response, NSError *error))completionHandler {
    [[self describeUserHierarchyStructure:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectDescribeUserHierarchyStructureResponse *> * _Nonnull task) {
        AWSConnectDescribeUserHierarchyStructureResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask *)disassociateApprovedOrigin:(AWSConnectDisassociateApprovedOriginRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodDELETE
                     URLString:@"/instance/{InstanceId}/approved-origin"
                  targetPrefix:@""
                 operationName:@"DisassociateApprovedOrigin"
                   outputClass:nil];
}

- (void)disassociateApprovedOrigin:(AWSConnectDisassociateApprovedOriginRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self disassociateApprovedOrigin:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)disassociateInstanceStorageConfig:(AWSConnectDisassociateInstanceStorageConfigRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodDELETE
                     URLString:@"/instance/{InstanceId}/storage-config/{AssociationId}"
                  targetPrefix:@""
                 operationName:@"DisassociateInstanceStorageConfig"
                   outputClass:nil];
}

- (void)disassociateInstanceStorageConfig:(AWSConnectDisassociateInstanceStorageConfigRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self disassociateInstanceStorageConfig:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)disassociateLambdaFunction:(AWSConnectDisassociateLambdaFunctionRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodDELETE
                     URLString:@"/instance/{InstanceId}/lambda-function"
                  targetPrefix:@""
                 operationName:@"DisassociateLambdaFunction"
                   outputClass:nil];
}

- (void)disassociateLambdaFunction:(AWSConnectDisassociateLambdaFunctionRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self disassociateLambdaFunction:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)disassociateLexBot:(AWSConnectDisassociateLexBotRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodDELETE
                     URLString:@"/instance/{InstanceId}/lex-bot"
                  targetPrefix:@""
                 operationName:@"DisassociateLexBot"
                   outputClass:nil];
}

- (void)disassociateLexBot:(AWSConnectDisassociateLexBotRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self disassociateLexBot:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)disassociateQueueQuickConnects:(AWSConnectDisassociateQueueQuickConnectsRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/queues/{InstanceId}/{QueueId}/disassociate-quick-connects"
                  targetPrefix:@""
                 operationName:@"DisassociateQueueQuickConnects"
                   outputClass:nil];
}

- (void)disassociateQueueQuickConnects:(AWSConnectDisassociateQueueQuickConnectsRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self disassociateQueueQuickConnects:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)disassociateRoutingProfileQueues:(AWSConnectDisassociateRoutingProfileQueuesRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/routing-profiles/{InstanceId}/{RoutingProfileId}/disassociate-queues"
                  targetPrefix:@""
                 operationName:@"DisassociateRoutingProfileQueues"
                   outputClass:nil];
}

- (void)disassociateRoutingProfileQueues:(AWSConnectDisassociateRoutingProfileQueuesRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self disassociateRoutingProfileQueues:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)disassociateSecurityKey:(AWSConnectDisassociateSecurityKeyRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodDELETE
                     URLString:@"/instance/{InstanceId}/security-key/{AssociationId}"
                  targetPrefix:@""
                 operationName:@"DisassociateSecurityKey"
                   outputClass:nil];
}

- (void)disassociateSecurityKey:(AWSConnectDisassociateSecurityKeyRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self disassociateSecurityKey:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectGetContactAttributesResponse *> *)getContactAttributes:(AWSConnectGetContactAttributesRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/contact/attributes/{InstanceId}/{InitialContactId}"
                  targetPrefix:@""
                 operationName:@"GetContactAttributes"
                   outputClass:[AWSConnectGetContactAttributesResponse class]];
}

- (void)getContactAttributes:(AWSConnectGetContactAttributesRequest *)request
     completionHandler:(void (^)(AWSConnectGetContactAttributesResponse *response, NSError *error))completionHandler {
    [[self getContactAttributes:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectGetContactAttributesResponse *> * _Nonnull task) {
        AWSConnectGetContactAttributesResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectGetCurrentMetricDataResponse *> *)getCurrentMetricData:(AWSConnectGetCurrentMetricDataRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/metrics/current/{InstanceId}"
                  targetPrefix:@""
                 operationName:@"GetCurrentMetricData"
                   outputClass:[AWSConnectGetCurrentMetricDataResponse class]];
}

- (void)getCurrentMetricData:(AWSConnectGetCurrentMetricDataRequest *)request
     completionHandler:(void (^)(AWSConnectGetCurrentMetricDataResponse *response, NSError *error))completionHandler {
    [[self getCurrentMetricData:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectGetCurrentMetricDataResponse *> * _Nonnull task) {
        AWSConnectGetCurrentMetricDataResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectGetFederationTokenResponse *> *)getFederationToken:(AWSConnectGetFederationTokenRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/user/federate/{InstanceId}"
                  targetPrefix:@""
                 operationName:@"GetFederationToken"
                   outputClass:[AWSConnectGetFederationTokenResponse class]];
}

- (void)getFederationToken:(AWSConnectGetFederationTokenRequest *)request
     completionHandler:(void (^)(AWSConnectGetFederationTokenResponse *response, NSError *error))completionHandler {
    [[self getFederationToken:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectGetFederationTokenResponse *> * _Nonnull task) {
        AWSConnectGetFederationTokenResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectGetMetricDataResponse *> *)getMetricData:(AWSConnectGetMetricDataRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/metrics/historical/{InstanceId}"
                  targetPrefix:@""
                 operationName:@"GetMetricData"
                   outputClass:[AWSConnectGetMetricDataResponse class]];
}

- (void)getMetricData:(AWSConnectGetMetricDataRequest *)request
     completionHandler:(void (^)(AWSConnectGetMetricDataResponse *response, NSError *error))completionHandler {
    [[self getMetricData:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectGetMetricDataResponse *> * _Nonnull task) {
        AWSConnectGetMetricDataResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectListApprovedOriginsResponse *> *)listApprovedOrigins:(AWSConnectListApprovedOriginsRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/instance/{InstanceId}/approved-origins"
                  targetPrefix:@""
                 operationName:@"ListApprovedOrigins"
                   outputClass:[AWSConnectListApprovedOriginsResponse class]];
}

- (void)listApprovedOrigins:(AWSConnectListApprovedOriginsRequest *)request
     completionHandler:(void (^)(AWSConnectListApprovedOriginsResponse *response, NSError *error))completionHandler {
    [[self listApprovedOrigins:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectListApprovedOriginsResponse *> * _Nonnull task) {
        AWSConnectListApprovedOriginsResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectListContactFlowsResponse *> *)listContactFlows:(AWSConnectListContactFlowsRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/contact-flows-summary/{InstanceId}"
                  targetPrefix:@""
                 operationName:@"ListContactFlows"
                   outputClass:[AWSConnectListContactFlowsResponse class]];
}

- (void)listContactFlows:(AWSConnectListContactFlowsRequest *)request
     completionHandler:(void (^)(AWSConnectListContactFlowsResponse *response, NSError *error))completionHandler {
    [[self listContactFlows:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectListContactFlowsResponse *> * _Nonnull task) {
        AWSConnectListContactFlowsResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectListHoursOfOperationsResponse *> *)listHoursOfOperations:(AWSConnectListHoursOfOperationsRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/hours-of-operations-summary/{InstanceId}"
                  targetPrefix:@""
                 operationName:@"ListHoursOfOperations"
                   outputClass:[AWSConnectListHoursOfOperationsResponse class]];
}

- (void)listHoursOfOperations:(AWSConnectListHoursOfOperationsRequest *)request
     completionHandler:(void (^)(AWSConnectListHoursOfOperationsResponse *response, NSError *error))completionHandler {
    [[self listHoursOfOperations:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectListHoursOfOperationsResponse *> * _Nonnull task) {
        AWSConnectListHoursOfOperationsResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectListInstanceAttributesResponse *> *)listInstanceAttributes:(AWSConnectListInstanceAttributesRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/instance/{InstanceId}/attributes"
                  targetPrefix:@""
                 operationName:@"ListInstanceAttributes"
                   outputClass:[AWSConnectListInstanceAttributesResponse class]];
}

- (void)listInstanceAttributes:(AWSConnectListInstanceAttributesRequest *)request
     completionHandler:(void (^)(AWSConnectListInstanceAttributesResponse *response, NSError *error))completionHandler {
    [[self listInstanceAttributes:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectListInstanceAttributesResponse *> * _Nonnull task) {
        AWSConnectListInstanceAttributesResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectListInstanceStorageConfigsResponse *> *)listInstanceStorageConfigs:(AWSConnectListInstanceStorageConfigsRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/instance/{InstanceId}/storage-configs"
                  targetPrefix:@""
                 operationName:@"ListInstanceStorageConfigs"
                   outputClass:[AWSConnectListInstanceStorageConfigsResponse class]];
}

- (void)listInstanceStorageConfigs:(AWSConnectListInstanceStorageConfigsRequest *)request
     completionHandler:(void (^)(AWSConnectListInstanceStorageConfigsResponse *response, NSError *error))completionHandler {
    [[self listInstanceStorageConfigs:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectListInstanceStorageConfigsResponse *> * _Nonnull task) {
        AWSConnectListInstanceStorageConfigsResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectListInstancesResponse *> *)listInstances:(AWSConnectListInstancesRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/instance"
                  targetPrefix:@""
                 operationName:@"ListInstances"
                   outputClass:[AWSConnectListInstancesResponse class]];
}

- (void)listInstances:(AWSConnectListInstancesRequest *)request
     completionHandler:(void (^)(AWSConnectListInstancesResponse *response, NSError *error))completionHandler {
    [[self listInstances:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectListInstancesResponse *> * _Nonnull task) {
        AWSConnectListInstancesResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectListIntegrationAssociationsResponse *> *)listIntegrationAssociations:(AWSConnectListIntegrationAssociationsRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/instance/{InstanceId}/integration-associations"
                  targetPrefix:@""
                 operationName:@"ListIntegrationAssociations"
                   outputClass:[AWSConnectListIntegrationAssociationsResponse class]];
}

- (void)listIntegrationAssociations:(AWSConnectListIntegrationAssociationsRequest *)request
     completionHandler:(void (^)(AWSConnectListIntegrationAssociationsResponse *response, NSError *error))completionHandler {
    [[self listIntegrationAssociations:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectListIntegrationAssociationsResponse *> * _Nonnull task) {
        AWSConnectListIntegrationAssociationsResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectListLambdaFunctionsResponse *> *)listLambdaFunctions:(AWSConnectListLambdaFunctionsRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/instance/{InstanceId}/lambda-functions"
                  targetPrefix:@""
                 operationName:@"ListLambdaFunctions"
                   outputClass:[AWSConnectListLambdaFunctionsResponse class]];
}

- (void)listLambdaFunctions:(AWSConnectListLambdaFunctionsRequest *)request
     completionHandler:(void (^)(AWSConnectListLambdaFunctionsResponse *response, NSError *error))completionHandler {
    [[self listLambdaFunctions:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectListLambdaFunctionsResponse *> * _Nonnull task) {
        AWSConnectListLambdaFunctionsResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectListLexBotsResponse *> *)listLexBots:(AWSConnectListLexBotsRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/instance/{InstanceId}/lex-bots"
                  targetPrefix:@""
                 operationName:@"ListLexBots"
                   outputClass:[AWSConnectListLexBotsResponse class]];
}

- (void)listLexBots:(AWSConnectListLexBotsRequest *)request
     completionHandler:(void (^)(AWSConnectListLexBotsResponse *response, NSError *error))completionHandler {
    [[self listLexBots:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectListLexBotsResponse *> * _Nonnull task) {
        AWSConnectListLexBotsResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectListPhoneNumbersResponse *> *)listPhoneNumbers:(AWSConnectListPhoneNumbersRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/phone-numbers-summary/{InstanceId}"
                  targetPrefix:@""
                 operationName:@"ListPhoneNumbers"
                   outputClass:[AWSConnectListPhoneNumbersResponse class]];
}

- (void)listPhoneNumbers:(AWSConnectListPhoneNumbersRequest *)request
     completionHandler:(void (^)(AWSConnectListPhoneNumbersResponse *response, NSError *error))completionHandler {
    [[self listPhoneNumbers:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectListPhoneNumbersResponse *> * _Nonnull task) {
        AWSConnectListPhoneNumbersResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectListPromptsResponse *> *)listPrompts:(AWSConnectListPromptsRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/prompts-summary/{InstanceId}"
                  targetPrefix:@""
                 operationName:@"ListPrompts"
                   outputClass:[AWSConnectListPromptsResponse class]];
}

- (void)listPrompts:(AWSConnectListPromptsRequest *)request
     completionHandler:(void (^)(AWSConnectListPromptsResponse *response, NSError *error))completionHandler {
    [[self listPrompts:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectListPromptsResponse *> * _Nonnull task) {
        AWSConnectListPromptsResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectListQueueQuickConnectsResponse *> *)listQueueQuickConnects:(AWSConnectListQueueQuickConnectsRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/queues/{InstanceId}/{QueueId}/quick-connects"
                  targetPrefix:@""
                 operationName:@"ListQueueQuickConnects"
                   outputClass:[AWSConnectListQueueQuickConnectsResponse class]];
}

- (void)listQueueQuickConnects:(AWSConnectListQueueQuickConnectsRequest *)request
     completionHandler:(void (^)(AWSConnectListQueueQuickConnectsResponse *response, NSError *error))completionHandler {
    [[self listQueueQuickConnects:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectListQueueQuickConnectsResponse *> * _Nonnull task) {
        AWSConnectListQueueQuickConnectsResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectListQueuesResponse *> *)listQueues:(AWSConnectListQueuesRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/queues-summary/{InstanceId}"
                  targetPrefix:@""
                 operationName:@"ListQueues"
                   outputClass:[AWSConnectListQueuesResponse class]];
}

- (void)listQueues:(AWSConnectListQueuesRequest *)request
     completionHandler:(void (^)(AWSConnectListQueuesResponse *response, NSError *error))completionHandler {
    [[self listQueues:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectListQueuesResponse *> * _Nonnull task) {
        AWSConnectListQueuesResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectListQuickConnectsResponse *> *)listQuickConnects:(AWSConnectListQuickConnectsRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/quick-connects/{InstanceId}"
                  targetPrefix:@""
                 operationName:@"ListQuickConnects"
                   outputClass:[AWSConnectListQuickConnectsResponse class]];
}

- (void)listQuickConnects:(AWSConnectListQuickConnectsRequest *)request
     completionHandler:(void (^)(AWSConnectListQuickConnectsResponse *response, NSError *error))completionHandler {
    [[self listQuickConnects:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectListQuickConnectsResponse *> * _Nonnull task) {
        AWSConnectListQuickConnectsResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectListRoutingProfileQueuesResponse *> *)listRoutingProfileQueues:(AWSConnectListRoutingProfileQueuesRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/routing-profiles/{InstanceId}/{RoutingProfileId}/queues"
                  targetPrefix:@""
                 operationName:@"ListRoutingProfileQueues"
                   outputClass:[AWSConnectListRoutingProfileQueuesResponse class]];
}

- (void)listRoutingProfileQueues:(AWSConnectListRoutingProfileQueuesRequest *)request
     completionHandler:(void (^)(AWSConnectListRoutingProfileQueuesResponse *response, NSError *error))completionHandler {
    [[self listRoutingProfileQueues:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectListRoutingProfileQueuesResponse *> * _Nonnull task) {
        AWSConnectListRoutingProfileQueuesResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectListRoutingProfilesResponse *> *)listRoutingProfiles:(AWSConnectListRoutingProfilesRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/routing-profiles-summary/{InstanceId}"
                  targetPrefix:@""
                 operationName:@"ListRoutingProfiles"
                   outputClass:[AWSConnectListRoutingProfilesResponse class]];
}

- (void)listRoutingProfiles:(AWSConnectListRoutingProfilesRequest *)request
     completionHandler:(void (^)(AWSConnectListRoutingProfilesResponse *response, NSError *error))completionHandler {
    [[self listRoutingProfiles:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectListRoutingProfilesResponse *> * _Nonnull task) {
        AWSConnectListRoutingProfilesResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectListSecurityKeysResponse *> *)listSecurityKeys:(AWSConnectListSecurityKeysRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/instance/{InstanceId}/security-keys"
                  targetPrefix:@""
                 operationName:@"ListSecurityKeys"
                   outputClass:[AWSConnectListSecurityKeysResponse class]];
}

- (void)listSecurityKeys:(AWSConnectListSecurityKeysRequest *)request
     completionHandler:(void (^)(AWSConnectListSecurityKeysResponse *response, NSError *error))completionHandler {
    [[self listSecurityKeys:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectListSecurityKeysResponse *> * _Nonnull task) {
        AWSConnectListSecurityKeysResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectListSecurityProfilesResponse *> *)listSecurityProfiles:(AWSConnectListSecurityProfilesRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/security-profiles-summary/{InstanceId}"
                  targetPrefix:@""
                 operationName:@"ListSecurityProfiles"
                   outputClass:[AWSConnectListSecurityProfilesResponse class]];
}

- (void)listSecurityProfiles:(AWSConnectListSecurityProfilesRequest *)request
     completionHandler:(void (^)(AWSConnectListSecurityProfilesResponse *response, NSError *error))completionHandler {
    [[self listSecurityProfiles:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectListSecurityProfilesResponse *> * _Nonnull task) {
        AWSConnectListSecurityProfilesResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectListTagsForResourceResponse *> *)listTagsForResource:(AWSConnectListTagsForResourceRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/tags/{resourceArn}"
                  targetPrefix:@""
                 operationName:@"ListTagsForResource"
                   outputClass:[AWSConnectListTagsForResourceResponse class]];
}

- (void)listTagsForResource:(AWSConnectListTagsForResourceRequest *)request
     completionHandler:(void (^)(AWSConnectListTagsForResourceResponse *response, NSError *error))completionHandler {
    [[self listTagsForResource:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectListTagsForResourceResponse *> * _Nonnull task) {
        AWSConnectListTagsForResourceResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectListUseCasesResponse *> *)listUseCases:(AWSConnectListUseCasesRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/instance/{InstanceId}/integration-associations/{IntegrationAssociationId}/use-cases"
                  targetPrefix:@""
                 operationName:@"ListUseCases"
                   outputClass:[AWSConnectListUseCasesResponse class]];
}

- (void)listUseCases:(AWSConnectListUseCasesRequest *)request
     completionHandler:(void (^)(AWSConnectListUseCasesResponse *response, NSError *error))completionHandler {
    [[self listUseCases:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectListUseCasesResponse *> * _Nonnull task) {
        AWSConnectListUseCasesResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectListUserHierarchyGroupsResponse *> *)listUserHierarchyGroups:(AWSConnectListUserHierarchyGroupsRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/user-hierarchy-groups-summary/{InstanceId}"
                  targetPrefix:@""
                 operationName:@"ListUserHierarchyGroups"
                   outputClass:[AWSConnectListUserHierarchyGroupsResponse class]];
}

- (void)listUserHierarchyGroups:(AWSConnectListUserHierarchyGroupsRequest *)request
     completionHandler:(void (^)(AWSConnectListUserHierarchyGroupsResponse *response, NSError *error))completionHandler {
    [[self listUserHierarchyGroups:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectListUserHierarchyGroupsResponse *> * _Nonnull task) {
        AWSConnectListUserHierarchyGroupsResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectListUsersResponse *> *)listUsers:(AWSConnectListUsersRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodGET
                     URLString:@"/users-summary/{InstanceId}"
                  targetPrefix:@""
                 operationName:@"ListUsers"
                   outputClass:[AWSConnectListUsersResponse class]];
}

- (void)listUsers:(AWSConnectListUsersRequest *)request
     completionHandler:(void (^)(AWSConnectListUsersResponse *response, NSError *error))completionHandler {
    [[self listUsers:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectListUsersResponse *> * _Nonnull task) {
        AWSConnectListUsersResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectResumeContactRecordingResponse *> *)resumeContactRecording:(AWSConnectResumeContactRecordingRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/contact/resume-recording"
                  targetPrefix:@""
                 operationName:@"ResumeContactRecording"
                   outputClass:[AWSConnectResumeContactRecordingResponse class]];
}

- (void)resumeContactRecording:(AWSConnectResumeContactRecordingRequest *)request
     completionHandler:(void (^)(AWSConnectResumeContactRecordingResponse *response, NSError *error))completionHandler {
    [[self resumeContactRecording:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectResumeContactRecordingResponse *> * _Nonnull task) {
        AWSConnectResumeContactRecordingResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectStartChatContactResponse *> *)startChatContact:(AWSConnectStartChatContactRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPUT
                     URLString:@"/contact/chat"
                  targetPrefix:@""
                 operationName:@"StartChatContact"
                   outputClass:[AWSConnectStartChatContactResponse class]];
}

- (void)startChatContact:(AWSConnectStartChatContactRequest *)request
     completionHandler:(void (^)(AWSConnectStartChatContactResponse *response, NSError *error))completionHandler {
    [[self startChatContact:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectStartChatContactResponse *> * _Nonnull task) {
        AWSConnectStartChatContactResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectStartContactRecordingResponse *> *)startContactRecording:(AWSConnectStartContactRecordingRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/contact/start-recording"
                  targetPrefix:@""
                 operationName:@"StartContactRecording"
                   outputClass:[AWSConnectStartContactRecordingResponse class]];
}

- (void)startContactRecording:(AWSConnectStartContactRecordingRequest *)request
     completionHandler:(void (^)(AWSConnectStartContactRecordingResponse *response, NSError *error))completionHandler {
    [[self startContactRecording:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectStartContactRecordingResponse *> * _Nonnull task) {
        AWSConnectStartContactRecordingResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectStartOutboundVoiceContactResponse *> *)startOutboundVoiceContact:(AWSConnectStartOutboundVoiceContactRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPUT
                     URLString:@"/contact/outbound-voice"
                  targetPrefix:@""
                 operationName:@"StartOutboundVoiceContact"
                   outputClass:[AWSConnectStartOutboundVoiceContactResponse class]];
}

- (void)startOutboundVoiceContact:(AWSConnectStartOutboundVoiceContactRequest *)request
     completionHandler:(void (^)(AWSConnectStartOutboundVoiceContactResponse *response, NSError *error))completionHandler {
    [[self startOutboundVoiceContact:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectStartOutboundVoiceContactResponse *> * _Nonnull task) {
        AWSConnectStartOutboundVoiceContactResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectStartTaskContactResponse *> *)startTaskContact:(AWSConnectStartTaskContactRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPUT
                     URLString:@"/contact/task"
                  targetPrefix:@""
                 operationName:@"StartTaskContact"
                   outputClass:[AWSConnectStartTaskContactResponse class]];
}

- (void)startTaskContact:(AWSConnectStartTaskContactRequest *)request
     completionHandler:(void (^)(AWSConnectStartTaskContactResponse *response, NSError *error))completionHandler {
    [[self startTaskContact:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectStartTaskContactResponse *> * _Nonnull task) {
        AWSConnectStartTaskContactResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectStopContactResponse *> *)stopContact:(AWSConnectStopContactRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/contact/stop"
                  targetPrefix:@""
                 operationName:@"StopContact"
                   outputClass:[AWSConnectStopContactResponse class]];
}

- (void)stopContact:(AWSConnectStopContactRequest *)request
     completionHandler:(void (^)(AWSConnectStopContactResponse *response, NSError *error))completionHandler {
    [[self stopContact:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectStopContactResponse *> * _Nonnull task) {
        AWSConnectStopContactResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectStopContactRecordingResponse *> *)stopContactRecording:(AWSConnectStopContactRecordingRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/contact/stop-recording"
                  targetPrefix:@""
                 operationName:@"StopContactRecording"
                   outputClass:[AWSConnectStopContactRecordingResponse class]];
}

- (void)stopContactRecording:(AWSConnectStopContactRecordingRequest *)request
     completionHandler:(void (^)(AWSConnectStopContactRecordingResponse *response, NSError *error))completionHandler {
    [[self stopContactRecording:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectStopContactRecordingResponse *> * _Nonnull task) {
        AWSConnectStopContactRecordingResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectSuspendContactRecordingResponse *> *)suspendContactRecording:(AWSConnectSuspendContactRecordingRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/contact/suspend-recording"
                  targetPrefix:@""
                 operationName:@"SuspendContactRecording"
                   outputClass:[AWSConnectSuspendContactRecordingResponse class]];
}

- (void)suspendContactRecording:(AWSConnectSuspendContactRecordingRequest *)request
     completionHandler:(void (^)(AWSConnectSuspendContactRecordingResponse *response, NSError *error))completionHandler {
    [[self suspendContactRecording:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectSuspendContactRecordingResponse *> * _Nonnull task) {
        AWSConnectSuspendContactRecordingResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask *)tagResource:(AWSConnectTagResourceRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/tags/{resourceArn}"
                  targetPrefix:@""
                 operationName:@"TagResource"
                   outputClass:nil];
}

- (void)tagResource:(AWSConnectTagResourceRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self tagResource:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)untagResource:(AWSConnectUntagResourceRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodDELETE
                     URLString:@"/tags/{resourceArn}"
                  targetPrefix:@""
                 operationName:@"UntagResource"
                   outputClass:nil];
}

- (void)untagResource:(AWSConnectUntagResourceRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self untagResource:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask<AWSConnectUpdateContactAttributesResponse *> *)updateContactAttributes:(AWSConnectUpdateContactAttributesRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/contact/attributes"
                  targetPrefix:@""
                 operationName:@"UpdateContactAttributes"
                   outputClass:[AWSConnectUpdateContactAttributesResponse class]];
}

- (void)updateContactAttributes:(AWSConnectUpdateContactAttributesRequest *)request
     completionHandler:(void (^)(AWSConnectUpdateContactAttributesResponse *response, NSError *error))completionHandler {
    [[self updateContactAttributes:request] continueWithBlock:^id _Nullable(AWSTask<AWSConnectUpdateContactAttributesResponse *> * _Nonnull task) {
        AWSConnectUpdateContactAttributesResponse *result = task.result;
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(result, error);
        }

        return nil;
    }];
}

- (AWSTask *)updateContactFlowContent:(AWSConnectUpdateContactFlowContentRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/contact-flows/{InstanceId}/{ContactFlowId}/content"
                  targetPrefix:@""
                 operationName:@"UpdateContactFlowContent"
                   outputClass:nil];
}

- (void)updateContactFlowContent:(AWSConnectUpdateContactFlowContentRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self updateContactFlowContent:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)updateContactFlowName:(AWSConnectUpdateContactFlowNameRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/contact-flows/{InstanceId}/{ContactFlowId}/name"
                  targetPrefix:@""
                 operationName:@"UpdateContactFlowName"
                   outputClass:nil];
}

- (void)updateContactFlowName:(AWSConnectUpdateContactFlowNameRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self updateContactFlowName:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)updateInstanceAttribute:(AWSConnectUpdateInstanceAttributeRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/instance/{InstanceId}/attribute/{AttributeType}"
                  targetPrefix:@""
                 operationName:@"UpdateInstanceAttribute"
                   outputClass:nil];
}

- (void)updateInstanceAttribute:(AWSConnectUpdateInstanceAttributeRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self updateInstanceAttribute:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)updateInstanceStorageConfig:(AWSConnectUpdateInstanceStorageConfigRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/instance/{InstanceId}/storage-config/{AssociationId}"
                  targetPrefix:@""
                 operationName:@"UpdateInstanceStorageConfig"
                   outputClass:nil];
}

- (void)updateInstanceStorageConfig:(AWSConnectUpdateInstanceStorageConfigRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self updateInstanceStorageConfig:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)updateQueueHoursOfOperation:(AWSConnectUpdateQueueHoursOfOperationRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/queues/{InstanceId}/{QueueId}/hours-of-operation"
                  targetPrefix:@""
                 operationName:@"UpdateQueueHoursOfOperation"
                   outputClass:nil];
}

- (void)updateQueueHoursOfOperation:(AWSConnectUpdateQueueHoursOfOperationRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self updateQueueHoursOfOperation:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)updateQueueMaxContacts:(AWSConnectUpdateQueueMaxContactsRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/queues/{InstanceId}/{QueueId}/max-contacts"
                  targetPrefix:@""
                 operationName:@"UpdateQueueMaxContacts"
                   outputClass:nil];
}

- (void)updateQueueMaxContacts:(AWSConnectUpdateQueueMaxContactsRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self updateQueueMaxContacts:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)updateQueueName:(AWSConnectUpdateQueueNameRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/queues/{InstanceId}/{QueueId}/name"
                  targetPrefix:@""
                 operationName:@"UpdateQueueName"
                   outputClass:nil];
}

- (void)updateQueueName:(AWSConnectUpdateQueueNameRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self updateQueueName:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)updateQueueOutboundCallerConfig:(AWSConnectUpdateQueueOutboundCallerConfigRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/queues/{InstanceId}/{QueueId}/outbound-caller-config"
                  targetPrefix:@""
                 operationName:@"UpdateQueueOutboundCallerConfig"
                   outputClass:nil];
}

- (void)updateQueueOutboundCallerConfig:(AWSConnectUpdateQueueOutboundCallerConfigRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self updateQueueOutboundCallerConfig:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)updateQueueStatus:(AWSConnectUpdateQueueStatusRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/queues/{InstanceId}/{QueueId}/status"
                  targetPrefix:@""
                 operationName:@"UpdateQueueStatus"
                   outputClass:nil];
}

- (void)updateQueueStatus:(AWSConnectUpdateQueueStatusRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self updateQueueStatus:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)updateQuickConnectConfig:(AWSConnectUpdateQuickConnectConfigRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/quick-connects/{InstanceId}/{QuickConnectId}/config"
                  targetPrefix:@""
                 operationName:@"UpdateQuickConnectConfig"
                   outputClass:nil];
}

- (void)updateQuickConnectConfig:(AWSConnectUpdateQuickConnectConfigRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self updateQuickConnectConfig:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)updateQuickConnectName:(AWSConnectUpdateQuickConnectNameRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/quick-connects/{InstanceId}/{QuickConnectId}/name"
                  targetPrefix:@""
                 operationName:@"UpdateQuickConnectName"
                   outputClass:nil];
}

- (void)updateQuickConnectName:(AWSConnectUpdateQuickConnectNameRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self updateQuickConnectName:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)updateRoutingProfileConcurrency:(AWSConnectUpdateRoutingProfileConcurrencyRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/routing-profiles/{InstanceId}/{RoutingProfileId}/concurrency"
                  targetPrefix:@""
                 operationName:@"UpdateRoutingProfileConcurrency"
                   outputClass:nil];
}

- (void)updateRoutingProfileConcurrency:(AWSConnectUpdateRoutingProfileConcurrencyRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self updateRoutingProfileConcurrency:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)updateRoutingProfileDefaultOutboundQueue:(AWSConnectUpdateRoutingProfileDefaultOutboundQueueRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/routing-profiles/{InstanceId}/{RoutingProfileId}/default-outbound-queue"
                  targetPrefix:@""
                 operationName:@"UpdateRoutingProfileDefaultOutboundQueue"
                   outputClass:nil];
}

- (void)updateRoutingProfileDefaultOutboundQueue:(AWSConnectUpdateRoutingProfileDefaultOutboundQueueRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self updateRoutingProfileDefaultOutboundQueue:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)updateRoutingProfileName:(AWSConnectUpdateRoutingProfileNameRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/routing-profiles/{InstanceId}/{RoutingProfileId}/name"
                  targetPrefix:@""
                 operationName:@"UpdateRoutingProfileName"
                   outputClass:nil];
}

- (void)updateRoutingProfileName:(AWSConnectUpdateRoutingProfileNameRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self updateRoutingProfileName:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)updateRoutingProfileQueues:(AWSConnectUpdateRoutingProfileQueuesRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/routing-profiles/{InstanceId}/{RoutingProfileId}/queues"
                  targetPrefix:@""
                 operationName:@"UpdateRoutingProfileQueues"
                   outputClass:nil];
}

- (void)updateRoutingProfileQueues:(AWSConnectUpdateRoutingProfileQueuesRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self updateRoutingProfileQueues:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)updateUserHierarchy:(AWSConnectUpdateUserHierarchyRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/users/{InstanceId}/{UserId}/hierarchy"
                  targetPrefix:@""
                 operationName:@"UpdateUserHierarchy"
                   outputClass:nil];
}

- (void)updateUserHierarchy:(AWSConnectUpdateUserHierarchyRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self updateUserHierarchy:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)updateUserHierarchyGroupName:(AWSConnectUpdateUserHierarchyGroupNameRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/user-hierarchy-groups/{InstanceId}/{HierarchyGroupId}/name"
                  targetPrefix:@""
                 operationName:@"UpdateUserHierarchyGroupName"
                   outputClass:nil];
}

- (void)updateUserHierarchyGroupName:(AWSConnectUpdateUserHierarchyGroupNameRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self updateUserHierarchyGroupName:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)updateUserHierarchyStructure:(AWSConnectUpdateUserHierarchyStructureRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/user-hierarchy-structure/{InstanceId}"
                  targetPrefix:@""
                 operationName:@"UpdateUserHierarchyStructure"
                   outputClass:nil];
}

- (void)updateUserHierarchyStructure:(AWSConnectUpdateUserHierarchyStructureRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self updateUserHierarchyStructure:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)updateUserIdentityInfo:(AWSConnectUpdateUserIdentityInfoRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/users/{InstanceId}/{UserId}/identity-info"
                  targetPrefix:@""
                 operationName:@"UpdateUserIdentityInfo"
                   outputClass:nil];
}

- (void)updateUserIdentityInfo:(AWSConnectUpdateUserIdentityInfoRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self updateUserIdentityInfo:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)updateUserPhoneConfig:(AWSConnectUpdateUserPhoneConfigRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/users/{InstanceId}/{UserId}/phone-config"
                  targetPrefix:@""
                 operationName:@"UpdateUserPhoneConfig"
                   outputClass:nil];
}

- (void)updateUserPhoneConfig:(AWSConnectUpdateUserPhoneConfigRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self updateUserPhoneConfig:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)updateUserRoutingProfile:(AWSConnectUpdateUserRoutingProfileRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/users/{InstanceId}/{UserId}/routing-profile"
                  targetPrefix:@""
                 operationName:@"UpdateUserRoutingProfile"
                   outputClass:nil];
}

- (void)updateUserRoutingProfile:(AWSConnectUpdateUserRoutingProfileRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self updateUserRoutingProfile:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

- (AWSTask *)updateUserSecurityProfiles:(AWSConnectUpdateUserSecurityProfilesRequest *)request {
    return [self invokeRequest:request
                    HTTPMethod:AWSHTTPMethodPOST
                     URLString:@"/users/{InstanceId}/{UserId}/security-profiles"
                  targetPrefix:@""
                 operationName:@"UpdateUserSecurityProfiles"
                   outputClass:nil];
}

- (void)updateUserSecurityProfiles:(AWSConnectUpdateUserSecurityProfilesRequest *)request
     completionHandler:(void (^)(NSError *error))completionHandler {
    [[self updateUserSecurityProfiles:request] continueWithBlock:^id _Nullable(AWSTask * _Nonnull task) {
        NSError *error = task.error;

        if (completionHandler) {
            completionHandler(error);
        }

        return nil;
    }];
}

#pragma mark -

@end
