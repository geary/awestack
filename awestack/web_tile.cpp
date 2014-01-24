#include "web_tile.h"
#include "../common/sdl/gl_texture_surface.h"
#include <Awesomium/STLHelpers.h>

#if TRANSPARENT
#define TEX_FORMAT	GL_RGBA
#else
#define TEX_FORMAT	GL_RGB
#endif

using namespace Awesomium;

WebTile::WebTile(
	Application* app,
	const Awesomium::WebString id,
	int left, int top,
	int width, int height
) :
	m_app( app ),
	m_id( id ),
	m_left( left ),
	m_top( top ),
	m_width( width ),
	m_height( height ),
	isTransparent( true )
{
	webView = Awesomium::WebCore::instance()->CreateWebView(width, height);
	webView->CreateGlobalJavascriptObject( WSLit("AweStack") );
}

WebTile::WebTile(
	Application* app,
	const Awesomium::WebString id,
	Awesomium::WebView* existingWebView,
	int width, int height
) :
	m_app( app ),
	m_id(id),
	webView(existingWebView),
	isTransparent(false)
{
	m_id = id;
}

WebTile::~WebTile() {
	webView->Destroy();
}

const GLTextureSurface* WebTile::surface() {
	const Awesomium::Surface* surface = webView->surface();
	if (surface)
		return static_cast<const GLTextureSurface*>(surface);
	
	return 0;
}

void WebTile::resize(int width, int height) {
	webView->Resize(width, height);
}

void WebTile::toggleTransparency() {
	webView->ExecuteJavascript(WSLit("document.body.style.backgroundColor = 'transparent'"), WSLit(""));
	webView->SetTransparent(isTransparent = !isTransparent);
}

void WebTile::OnShowCreatedWebView(
	Awesomium::WebView* caller,
	Awesomium::WebView* new_view,
	const Awesomium::WebURL& opener_url,
	const Awesomium::WebURL& target_url,
	const Awesomium::Rect& initial_pos,
	bool is_popup
) {
}

void WebTile::OnBeginLoadingFrame(
	Awesomium::WebView* caller,
	int64 frame_id,
	bool is_main_frame,
	const Awesomium::WebURL& url,
	bool is_error_page
) {
}

void WebTile::OnFailLoadingFrame(
	Awesomium::WebView* caller,
	int64 frame_id,
	bool is_main_frame,
	const Awesomium::WebURL& url,
	int error_code,
	const Awesomium::WebString& error_description
) {
}

void WebTile::OnFinishLoadingFrame(
	Awesomium::WebView* caller,
	int64 frame_id,
	bool is_main_frame,
	const Awesomium::WebURL& url
) {
}

void WebTile::OnDocumentReady(
	Awesomium::WebView* caller,
	const Awesomium::WebURL& url
) {
	m_app->bindMethods( caller, m_id );
}
