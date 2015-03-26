﻿/* ***************************************************************************
 * widget_base.h -- the widget base operation set.
 *
 * Copyright (C) 2012-2014 by
 * Liu Chao
 *
 * This file is part of the LCUI project, and may only be used, modified, and
 * distributed under the terms of the GPLv2.
 *
 * (GPLv2 is abbreviation of GNU General Public License Version 2)
 *
 * By continuing to use, modify, or distribute this file you indicate that you
 * have read the license and understand and accept it fully.
 *
 * The LCUI project is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GPL v2 for more details.
 *
 * You should have received a copy of the GPLv2 along with this file. It is
 * usually in the LICENSE.TXT file, If not, see <http://www.gnu.org/licenses/>.
 * ****************************************************************************/

/* ****************************************************************************
 * widget_base.h -- 部件的基本操作集。
 *
 * 版权所有 (C) 2012-2014 归属于
 * 刘超
 *
 * 这个文件是LCUI项目的一部分，并且只可以根据GPLv2许可协议来使用、更改和发布。
 *
 * (GPLv2 是 GNU通用公共许可证第二版 的英文缩写)
 *
 * 继续使用、修改或发布本文件，表明您已经阅读并完全理解和接受这个许可协议。
 *
 * LCUI 项目是基于使用目的而加以散布的，但不负任何担保责任，甚至没有适销性或特
 * 定用途的隐含担保，详情请参照GPLv2许可协议。
 *
 * 您应已收到附随于本文件的GPLv2许可协议的副本，它通常在LICENSE.TXT文件中，如果
 * 没有，请查看：<http://www.gnu.org/licenses/>.
 * ****************************************************************************/

#ifndef __LCUI_WIDGET_BASE_H__
#define __LCUI_WIDGET_BASE_H__

/** 如果没有包含 widget_build.h 头文件 */
#ifndef __LCUI_WIDGET_BUILD_H__

typedef struct LCUI_WidgetBase* LCUI_Widget;

#endif

#ifdef $
#undef $
#endif

/** 
 * $ 可以看成是 self，部件操作函数的第一个参数类型都是LCUI_Widget，想用
 * 一个字符的来代替，以减少源代码的字符量，再加上又想试试 $，于是就用它了
 */
#define $ LCUI_Widget

/** 边框风格 */
enum LCUI_WidgetBorderStyle {
	BORDER_NONE,	/**< 无边框 */
	BORDER_SOLID,	/**< 实线 */
	BORDER_DOTTED,	/**< 点状 */
	BORDER_DOUBLE,	/**< 双线 */
	BORDER_DASHED	/**< 虚线 */
};

/** 框类型 */
typedef enum LCUI_WidgetBoxType {
	CONTENT_BOX,	/**< 内容框 */
	PADDING_BOX,	/**< 内边距框 */
	BORDER_BOX,	/**< 边框盒 */
	GRAPH_BOX	/**< 图形呈现框 */
} LCUI_WidgetBoxType;

typedef struct LCUI_WidgetBase {
	int x, y;			/**< 部件当前坐标 */
	int width, height;		/**< 部件区域大小，包括边框和内边距占用区域 */
	struct LCUI_WidgetBoxRect {
		LCUI_Rect content;	/**< 内容框的区域 */
		LCUI_Rect border;	/**< 边框盒的区域，包括内边距框和内容框区域 */
		LCUI_Rect outer;	/**< 外边框的区域，包括边框盒和外边距框区域 */
		LCUI_Rect graph;	/**< 图层的区域，包括边框盒和阴影区域 */
	} box;				/**< 部件的各个区域信息 */
	LCUI_Rect2 padding;		/**< 内边框 */
	LCUI_Rect2 margin;		/**< 外边框 */
} LCUI_WidgetBase;

#undef $

/** 上面用完 $，接着用 $ 定义个宏，为函数加前缀名 */
#define $(FUNC_NAME) Widget_##FUNC_NAME

/** 一般来说部件占用的矩形区域看上去是指边框盒区域 */
#define Widget_GetRect Widget_GetBorderRect

extern LCUI_Widget LCUIRootWidget;	/**< 根级部件 */

/** 新建一个GUI部件 */
LCUI_API LCUI_Widget $(New)( const char *type_name );

/** 获取当前点命中的最上层可见部件 */
LCUI_API LCUI_Widget $(At)( LCUI_Widget widget, int x, int y );

/** 设置部件为顶级部件 */
LCUI_API int $(Top)( LCUI_Widget w );
/** 获取内边距框占用的矩形区域 */
LCUI_API void $(GetPaddingRect)( LCUI_Widget widget, LCUI_Rect *rect );

/** 获取内容框占用的矩形区域 */
LCUI_API void $(GetContentRect)( LCUI_Widget widget, LCUI_Rect *rect );

/** 获取边框盒占用的矩形区域 */
LCUI_API void $(GetBorderRect)( LCUI_Widget widget, LCUI_Rect *rect );

/** 获取部件当前占用的矩形区域（包括阴影区域） */
LCUI_API void $(GetOuterRect)( LCUI_Widget widget, LCUI_Rect *rect );

LCUI_API void $(Resize)( LCUI_Widget w, int width, int height );

LCUI_API void $(Show)( LCUI_Widget w );

LCUI_API void $(Hide)( LCUI_Widget w );

LCUI_API void $(SetBackgroundColor)( LCUI_Widget w, LCUI_Color color );

LCUI_API void LCUIModule_Widget_Init(void);

#undef $

#endif
