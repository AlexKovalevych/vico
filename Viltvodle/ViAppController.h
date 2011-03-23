@class ViRegexp;

@protocol ViShellThingProtocol <NSObject>

- (void)exit;
- (void)exitWithObject:(id)obj;
- (void)exitWithError:(int)code;
- (void)log:(NSString *)message;

@end

@protocol ViShellCommandProtocol <NSObject>

- (NSString *)eval:(NSString *)script
    withScriptPath:(NSString *)path
additionalBindings:(NSDictionary *)bindings
       errorString:(NSString **)errorString
       backChannel:(NSString *)channelName;
- (NSError *)openURL:(NSString *)pathOrURL;

@end

@interface ViAppController : NSObject <ViShellCommandProtocol>
{
	IBOutlet NSMenu *encodingMenu;
	IBOutlet NSTextField *scriptInput;
	IBOutlet NSTextView *scriptOutput;
	NSMutableDictionary *sharedBuffers;
	NSConnection *shellConn;
}

@property(readonly) NSMenu *encodingMenu;

- (id)evalExpression:(NSString *)expression error:(NSError **)outError;

+ (NSString *)supportDirectory;
- (IBAction)showPreferences:(id)sender;

- (NSMutableDictionary *)sharedBuffers;

@end
