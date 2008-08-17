#import <Cocoa/Cocoa.h>
#import <OgreKit/OgreKit.h>
#import "ViCommand.h"
#import "ViTheme.h"
#import "ViLanguage.h"

#ifdef IMAX
# undef IMAX
#endif
#define IMAX(a, b)  (((NSInteger)a) > ((NSInteger)b) ? (a) : (b))

typedef enum { ViCommandMode, ViInsertMode } ViMode;

@interface ViTextView : NSTextView
{
	ViMode mode;
	ViCommand *parser;
	NSTextStorage *storage;
	NSMutableString *insertedText;

	NSMutableDictionary *buffers;
	NSRect oldCaretRect;
	NSRange affectedRange;
	NSUInteger start_location, end_location, final_location;
	BOOL need_scroll;

	NSMutableCharacterSet *wordSet;
	NSMutableCharacterSet *nonWordSet;
	NSCharacterSet *whitespace;

	/* syntax highlighting */
	ViTheme *theme;
	ViLanguage *language;

	CGFloat pageGuideX;

	int indent;
	unsigned regexps_tried;
	unsigned regexps_overlapped;
	unsigned regexps_matched;
}

- (void)initEditor;
- (void)setFilename:(NSURL *)aURL;
- (void)getLineStart:(NSUInteger *)bol_ptr end:(NSUInteger *)end_ptr contentsEnd:(NSUInteger *)eol_ptr forLocation:(NSUInteger)aLocation;
- (void)getLineStart:(NSUInteger *)bol_ptr end:(NSUInteger *)end_ptr contentsEnd:(NSUInteger *)eol_ptr;
- (void)gotoColumn:(NSUInteger)column fromLocation:(NSUInteger)aLocation;
- (void)setCommandMode;
- (void)setInsertMode;
- (void)input:(NSString *)inputString;
- (void)setCaret:(NSUInteger)location;
- (NSUInteger)caret;
- (void)setTheme:(ViTheme *)aTheme;
- (void)setTabSize:(int)tabSize;
@end

@interface ViTextView (cursor)
- (void)updateInsertionPoint;
@end

@interface ViTextView (syntax)
- (void)highlightEverything;
@end
