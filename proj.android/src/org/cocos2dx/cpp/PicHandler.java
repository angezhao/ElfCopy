package org.cocos2dx.cpp;

import java.io.File;

import org.cocos2dx.lib.Cocos2dxHelper;

import android.content.Intent;
import android.net.Uri;

import android.provider.MediaStore;
import android.util.Log;

public class PicHandler {

	public static void pickPhoto() {
		Log.d("pickPhoto", "pickPhoto");

		Intent intent = new Intent(Intent.ACTION_PICK, null);
		intent.setDataAndType(MediaStore.Images.Media.EXTERNAL_CONTENT_URI,
				"image/png"); // --"image/jpeg 、 image/png等的类型"
		// UserInfoActivity.getInstance().startActivityForResult(intent,
		// UserInfoActivity.HANDLER_SELECT_PIC);

		Cocos2dxHelper.getActivity().startActivityForResult(intent,
				AppActivity.HANDLER_SELECT_PIC);

	}

	public static void callCamera() {
		Log.d("callCamera", "callCamera");

		Intent intent = new Intent(MediaStore.ACTION_IMAGE_CAPTURE);
		intent.putExtra(
				MediaStore.EXTRA_OUTPUT,
				Uri.fromFile(new File(Cocos2dxHelper.getActivity()
						.getFilesDir().getAbsolutePath(), "temp.jpg")));
		Cocos2dxHelper.getActivity().startActivityForResult(intent,
				AppActivity.HANDLER_CALL_CAMERA);

	}
}
