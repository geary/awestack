#ifndef __WEB_TILE_H__
#define __WEB_TILE_H__

#include "application.h"
#include "../common/sdl/gl_texture_surface.h"

// A "WebTile" is essentially a WebView assigned to an OpenGL texture.
struct WebTile :
	public Awesomium::WebViewListener::Load
{
	Awesomium::WebView* webView;
	Application* m_app;
	Awesomium::WebString m_id;
	bool isTransparent;
	int m_left;
	int m_top;
	int m_width;
	int m_height;

	WebTile(
		Application* app,
		const Awesomium::WebString id,
		int left, int top,
		int width, int height
	);

	WebTile(
		Application* app,
		const Awesomium::WebString id,
		Awesomium::WebView* existingWebView,
		int width, int height
	);

	~WebTile();

	const GLTextureSurface* surface();

	void resize(int width, int height);
	void toggleTransparency();

	virtual void OnShowCreatedWebView(
		Awesomium::WebView* caller,
		Awesomium::WebView* new_view,
		const Awesomium::WebURL& opener_url,
		const Awesomium::WebURL& target_url,
		const Awesomium::Rect& initial_pos,
		bool is_popup
	);

	virtual void OnBeginLoadingFrame(
		Awesomium::WebView* caller,
		int64 frame_id,
		bool is_main_frame,
		const Awesomium::WebURL& url,
		bool is_error_page
	);

	virtual void OnFailLoadingFrame(
		Awesomium::WebView* caller,
		int64 frame_id,
		bool is_main_frame,
		const Awesomium::WebURL& url,
		int error_code,
		const Awesomium::WebString& error_description
	);

	virtual void OnFinishLoadingFrame(
		Awesomium::WebView* caller,
		int64 frame_id,
		bool is_main_frame,
		const Awesomium::WebURL& url
	);

	virtual void OnDocumentReady(
		Awesomium::WebView* caller,
		const Awesomium::WebURL& url
	);
};

#endif
