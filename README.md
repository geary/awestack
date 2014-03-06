**AweStack** is a sample application for the [Awesomium SDK](http://www.awesomium.com/) that supports multithreaded "stacks" of web pages which transparently overlay each other, with each page running in its own thread.

Normally, browsers&#8202;&mdash;&#8202;including the `WebView` object in Awesomium&#8202;&mdash;&#8202;use `<iframe>` elements to pull other pages into a single display. All of these pages run on a single thread, so if one `iframe` blocks the CPU, the entire page stops.   

AweStack creates multiple `WebView` objects containing individual web pages, using OpenGL to composite them onto a single display surface. Visually, it's just like having transparent `iframes`, but instead of all running on one thread, each one gets its own process or thread.

AweStack loads a single HTML page first, and provides a JavaScript API for that page to create and manage additional pages in the stack, and to post messages back and forth among the pages.

(API documentation coming soon!)