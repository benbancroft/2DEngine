package uk.co.benbancroft.AndroidEngine;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import uk.co.benbancroft.AndroidEngine.platform.PlatformFileUtils;
import android.content.Context;
import android.opengl.GLSurfaceView.Renderer;

public class RendererWrapper implements Renderer {
	static {
                System.loadLibrary("Android");
	}

	private final Context context;

	public RendererWrapper(Context context) {
		this.context = context;
	}

        public void handleTouchPress(float normalizedX, float normalizedY) {
            on_touch_press(normalizedX, normalizedY);
        }

        public void handleTouchDrag(float normalizedX, float normalizedY) {
            on_touch_drag(normalizedX, normalizedY);
        }

        private static native void on_touch_press(float normalized_x, float normalized_y);

        private static native void on_touch_drag(float normalized_x, float normalized_y);

	@Override
	public void onSurfaceCreated(GL10 gl, EGLConfig config) {
		PlatformFileUtils.init_asset_manager(context.getAssets());
		on_surface_created();
	}

	@Override
	public void onSurfaceChanged(GL10 gl, int width, int height) {
		on_surface_changed(width, height);
	}

	@Override
	public void onDrawFrame(GL10 gl) {
		on_draw_frame();
	}

	private static native void on_surface_created();

	private static native void on_surface_changed(int width, int height);

	private static native void on_draw_frame();
}
