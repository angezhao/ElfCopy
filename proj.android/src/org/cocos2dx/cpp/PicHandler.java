package org.cocos2dx.cpp;

import java.io.File;

import org.cocos2dx.lib.Cocos2dxHelper;

import android.content.Intent;
import android.net.Uri;
import android.os.Environment;

import android.provider.MediaStore;
import android.util.Log;

public class PicHandler {
	
	private static String path = Environment.getExternalStorageDirectory() + "/tmp";
	private static String name = "temp.jpg";
	public static String getPhotoPath(){
		return path + "/" + name;
	}

	public static void getPhoto(boolean takePhoto) {
		if (takePhoto) {
			callCamera();
		} else {
			pickPhoto();
		}
	}

	public static void pickPhoto() {
		Log.d("pickPhoto", "pickPhoto");

		Intent intent = new Intent(Intent.ACTION_GET_CONTENT);
		/*
		 * intent.addCategory(Intent.CATEGORY_OPENABLE);
		 * //intent.setDataAndType(MediaStore.Images.Media.EXTERNAL_CONTENT_URI,
		 * // "image/*"); // --"image/jpeg 、 image/png等的类型"
		 * intent.setType("image/*"); intent.putExtra("crop", "true");
		 * intent.putExtra("aspectX", 1); intent.putExtra("aspectY", 1);
		 * intent.putExtra("outputX", 150); intent.putExtra("outputY", 200);
		 * intent.putExtra("return-data", true);
		 */
		intent.setType("image/*");
		intent.putExtra("return-data", true);
		Cocos2dxHelper.getActivity().startActivityForResult(intent,
				AppActivity.HANDLER_SELECT_PIC);

	}

	public static void callCamera() {

		Log.d("callCamera", "callCamera");

		Intent intent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);

		Uri imgUri = Uri.fromFile(new File(path, name));

		intent.putExtra(MediaStore.EXTRA_OUTPUT, imgUri);
		
		intent.putExtra("return-data", true);

		Log.d("pichandler", imgUri.getPath());

		Cocos2dxHelper.getActivity().startActivityForResult(intent,
				AppActivity.HANDLER_CALL_CAMERA);

	}
}
