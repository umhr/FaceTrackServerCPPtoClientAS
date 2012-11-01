package  
{
	
	import flash.display.Shape;
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.geom.Rectangle;
	/**
	 * ...
	 * @author umhr
	 */
	public class Canvas extends Sprite 
	{
		private var _marker:Shape = new Shape();
		public function Canvas() 
		{
			init();
		}
		private function init():void 
		{
            if (stage) onInit();
            else addEventListener(Event.ADDED_TO_STAGE, onInit);
        }
        
        private function onInit(event:Event = null):void 
        {
			removeEventListener(Event.ADDED_TO_STAGE, onInit);
			// entry point
			
			SocketManager.getInstance();
			addChild(UICanvas.getInstance());
			addChild(FaceStageManager.getInstance());
			
			// ステージサイズに合わせた位置にダミーを置く用
			//addChild(_marker);
			//FaceStageManager.getInstance().addEventListener(Event.CHANGE, change);
			
		}
		
		private function change(e:Event):void 
		{
			_marker.graphics.clear();
			_marker.graphics.beginFill(0x00FF00);
			
			var rectangleList:Vector.<Rectangle> = FaceStageManager.getInstance().rectangleList;
			var n:int = rectangleList.length;
			for (var i:int = 0; i < n; i++) 
			{
				var rectangle:Rectangle = rectangleList[i];
				var tx:Number = ( 1 - ((rectangle.x + rectangle.width* 0.5 ) / 320)) * stage.stageWidth;
				var ty:Number = ((rectangle.y + rectangle.height * 0.5) / 240) * stage.stageHeight;
				
				_marker.graphics.drawCircle( tx, ty, 20);
				
			}
			_marker.graphics.endFill();
		}
	}
	
}