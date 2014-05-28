/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

import org.cocos2dx.lib.Cocos2dxActivity;
import org.cocos2dx.lib.Cocos2dxHelper;

import android.content.ContentResolver;
import android.content.Intent;
import android.database.Cursor;
import android.graphics.Bitmap;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;

public class AppActivity extends Cocos2dxActivity {
	public final static int HANDLER_CALL_CAMERA = 1;
	public final static int HANDLER_SELECT_PIC = 2;
	public final static int PICTURE_CLIPPING = 3;
	
	public static native void setPhotoPath(String path);
		
	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data){
		 super.onActivityResult(requestCode, resultCode, data);
		  Log.d("值", "返回值:requestCode" + requestCode + "resultCode = "
		    + resultCode);
		  if (resultCode != RESULT_OK) {
			  return;
		  }
		  
		  String path = null;
		  switch (requestCode) {
			  case AppActivity.HANDLER_CALL_CAMERA:
				//  startPhotoZoom(data.getData());				 
				  path = PicHandler.getPhotoPath();
				  Log.d("AppActivity", path);
				  setPhotoPath(path);
				  break;
			  // 取得裁剪后的图片
			  case AppActivity.HANDLER_SELECT_PIC:
				  path = this.getPhotoPath(data);
				  Log.d("AppActivity", path);
				  setPhotoPath(path);
				//  startPhotoZoom(data.getData());
				  /*
				   if (data != null) {
				    if (setPicToView(data) == RESULT_OK) {
				     //--选取头像成功，通知c++层
				    // JavaToC.touxiangIsOk(true);
				    } else {
				   //  JavaToC.touxiangIsOk(false);
				    }
				   }
				   */
				   break;
				   
				   
			  case AppActivity.PICTURE_CLIPPING:
				/*  if (data != null) {
					    if (setPicToView(data) == RESULT_OK) {
					     //--选取头像成功，通知c++层
					    // JavaToC.touxiangIsOk(true);
					    } else {
					   //  JavaToC.touxiangIsOk(false);
					    }
				  }
				  */
				  break;
			   
			  default:
				  break;
		  }
	}
	
	
	 /**
	  * 裁剪图片方法实现
	  * @param uri
	  */
	 public void startPhotoZoom(Uri uri) {
		  Intent intent = new Intent("com.android.camera.action.CROP");
		  intent.setDataAndType(uri, "image/*");
		  // 下面这个crop=true是设置在开启的Intent中设置显示的VIEW可裁剪
		  intent.putExtra("crop", "true");
		  // aspectX aspectY 是宽高的比例
		  intent.putExtra("aspectX", 1);
		  intent.putExtra("aspectY", 1);
		  // outputX outputY 是裁剪图片宽高
		  intent.putExtra("outputX", 150);
		  intent.putExtra("outputY", 150);
		  intent.putExtra("return-data", true);
		  startActivityForResult(intent, AppActivity.PICTURE_CLIPPING);
	 }
	 
	 /**
	  * 保存裁剪之后的图片数据
	  * @param picdata
	  */
	 private int setPicToView(Intent picdata) {
	  int result = RESULT_CANCELED;
	  Bundle extras = picdata.getExtras();
	  if (extras != null) {
	   Bitmap photo = extras.getParcelable("data");
	   String savePath = Environment.getExternalStorageDirectory()
	     + "/elfcopy/rectPhoto/" + "tou1" + ".png";
	   try {
	    result = bitmap2file(photo, savePath);
	   } catch (Exception e) {
	    result = RESULT_CANCELED;
	    // TODO Auto-generated catch block
	    e.printStackTrace();
	   }
	  }
	  return result;
	 }
	 
	 private String getPhotoPath(Intent data){
		 Uri uri = data.getData();
		 ContentResolver resolver = getContentResolver();
		 
		 Cursor cursor = resolver.query(uri, null, null, null, null);
		 cursor.moveToFirst();
		 String path =  cursor.getString(1);  //  获取的是图片的绝对路径
		 cursor.close();
		 
		 return path;
	 }

	 /**
	  * 将bitmap保存到本地png文件
	  * @param b
	  * @param fileName
	  * @throws Exception
	  */
	 private int bitmap2file(Bitmap b, String fileName) throws Exception {
	  int result = RESULT_CANCELED;
	  File myCaptureFile = new File(fileName);
	  Log.d("路径", "后面是路径" + myCaptureFile);
	  try {
		   BufferedOutputStream bos = new BufferedOutputStream(
		     new FileOutputStream(myCaptureFile));
		   b.compress(Bitmap.CompressFormat.PNG, 80, bos);
		   bos.flush();
		   bos.close();
		   result = RESULT_OK;
	   
	  } catch (FileNotFoundException e) {
		   // TODO Auto-generated catch block
		   result = RESULT_CANCELED;
		   e.printStackTrace();
	  } catch (IOException e) {
		   // TODO Auto-generated catch block
		   result = RESULT_CANCELED;
		   e.printStackTrace();
	  }
	  return result;
	 }

		@Override
		public void onWindowFocusChanged(final boolean hasWindowFocus) {
			super.onWindowFocusChanged(hasWindowFocus);
			Log.d("AppActivity", "ACTIVITY ON WINDOW FOCUS CHANGED " + (hasWindowFocus ? "true" : "false"));
			if (hasWindowFocus) {
				Cocos2dxHelper.onResume();
				this.mGLSurfaceView.onResume();
			} else {
				Cocos2dxHelper.onPause();
				this.mGLSurfaceView.onPause();
			}
	  	}
	 
}
