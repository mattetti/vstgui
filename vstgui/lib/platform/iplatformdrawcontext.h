// This file is part of VSTGUI. It is subject to the license terms
// in the LICENSE file found in the top-level directory of this
// distribution and at http://github.com/steinbergmedia/vstgui/LICENSE

#pragma once

#include "../vstguifwd.h"
#include <vector>

namespace VSTGUI {
namespace Platform {

//------------------------------------------------------------------------------------
enum class DrawStyle
{
	Stroked,
	Filled,
	FilledAndStroked,
};

//------------------------------------------------------------------------------------
enum class PathDrawMode
{
	Filled,
	FilledEvenOdd,
	Stroked,
};

//------------------------------------------------------------------------------------
enum class BitmapInterpolationQuality
{
	SystemDefault,
	Nearest,
	BilinearInterpolation,
	BicubicInterpolation
};

//------------------------------------------------------------------------------------
class IDrawDevice
{
public:
	using LinePair = std::pair<CPoint, CPoint>;
	using LineList = std::vector<LinePair>;
	using PointList = std::vector<CPoint>;
	using TransformMatrix = CGraphicsTransform;
	using LineStyle = CLineStyle;

	virtual void beginDraw () = 0;
	virtual void endDraw () = 0;

	virtual void drawLine (const LinePair& line) = 0;
	virtual void drawLines (const LineList& lines) = 0;
	virtual void drawPolygon (const PointList& polygonPointList,
	                          DrawStyle drawStyle = DrawStyle::Stroked) = 0;
	virtual void drawRect (const CRect& rect, DrawStyle drawStyle = DrawStyle::Stroked) = 0;
	virtual void drawArc (const CRect& rect, float startAngle1, float endAngle2,
	                      DrawStyle drawStyle = DrawStyle::Stroked) = 0;
	virtual void drawEllipse (const CRect& rect, DrawStyle drawStyle = DrawStyle::Stroked) = 0;
	virtual void drawPoint (const CPoint& point, const CColor& color) = 0;
	virtual void drawBitmap (IPlatformBitmap& bitmap, const CRect& dest,
	                         const CPoint& offset = CPoint (0, 0), float alpha = 1.f) = 0;
	/**
	 *	@return true if supported and drawn
	 */
	virtual bool drawBitmapNinePartTiled (IPlatformBitmap& bitmap, const CRect& dest,
	                                      const CNinePartTiledDescription& desc, float alpha = 1.f);
	/**
	 *	@return true if supported and drawn
	 */
	virtual bool fillRectWithBitmap (IPlatformBitmap& bitmap, const CRect& srcRect,
	                                 const CRect& dstRect, float alpha);
	virtual void clearRect (const CRect& rect) = 0;

	virtual void drawGraphicsPath (IPlatformGraphicsPath& path,
	                               PathDrawMode mode = PathDrawMode::Filled,
	                               TransformMatrix* tm = nullptr) = 0;
	virtual void fillLinearGradient (IPlatformGraphicsPath& path, IPlatformGradient& gradient,
	                                 const CPoint& startPoint, const CPoint& endPoint,
	                                 bool evenOdd = false, TransformMatrix* tm = nullptr) = 0;
	virtual void fillRadialGradient (IPlatformGraphicsPath& path, IPlatformGradient& gradient,
	                                 const CPoint& center, CCoord radius,
	                                 const CPoint& originOffset = CPoint (0, 0),
	                                 bool evenOdd = false, TransformMatrix* tm = nullptr) = 0;

	virtual void drawString (IPlatformFont& font, IPlatformString& string, const CPoint& point,
	                         bool antialias = true) = 0;
	virtual CCoord getStringWidth (IPlatformFont& font, IPlatformString& string,
	                               bool antialias = true) = 0;

	virtual void setClipRect (const CRect& clip);

	virtual void setLineStyle (const LineStyle& style) = 0;
	virtual void setLineWidth (CCoord width) = 0;

	virtual void setFillColor (const CColor& color) = 0;
	virtual void setFrameColor (const CColor& color) = 0;
	virtual void setFontColor (const CColor& color) = 0;
	virtual void setGlobalAlpha (float newAlpha) = 0;
	virtual void setBitmapInterpolationQuality (BitmapInterpolationQuality quality) = 0;

	virtual void concatTransform (const TransformMatrix& tm);

	virtual void saveGlobalState () = 0;
	virtual void restoreGlobalState () = 0;

	virtual ~IDrawDevice () noexcept = default;
};

} // Platform
} // VSTGUI
