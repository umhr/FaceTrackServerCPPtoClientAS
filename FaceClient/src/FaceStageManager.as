package  
{
	import flash.display.Sprite;
	import flash.events.Event;
	import flash.geom.Rectangle;
	/**
	 * ...
	 * @author umhr
	 */
	public class FaceStageManager extends Sprite
	{
		private static var _instance:FaceStageManager;
		public function FaceStageManager(block:SingletonBlock){init();}
		public static function getInstance():FaceStageManager{
			if ( _instance == null ) {_instance = new FaceStageManager(new SingletonBlock());};
			return _instance;
		}
		
		private var _rectangleList:Vector.<Rectangle> = new Vector.<Rectangle>();
		private function init():void
		{
		}
		
		public function setPosition(data:String):void {
			
			graphics.clear();
			
			if (data.length < 10) { return };
			
			rectangleList.length = 0;
			
			data = data.replace(/[\t\n\r\f]/g, "");
			//trace(data);
			
			graphics.beginFill(0xFF0000);
			
			var rectList:Array = data.split("{");
			var n:int = rectList.length;
			for (var i:int = 1; i < n; i++) 
			{
				var rectangle:Rectangle = new Rectangle();
				var rectStr:String = rectList[i];
				rectStr = rectStr.substr(0, rectStr.length - 1);
				var posList:Array = rectStr.split(",");
				var m:int = posList.length;
				for (var j:int = 1; j < m; j++) 
				{
					var str:String = posList[j];
					var paramList:Array = str.split(":");
					
					if(paramList[0] && !isNaN(paramList[1])){
						rectangle[paramList[0]] = Number(paramList[1]);
					}
					
				}
				
				graphics.drawRect(rectangle.x, rectangle.y, rectangle.width, rectangle.height);
				
				_rectangleList.push(rectangle);
			}
			graphics.endFill();
			
			dispatchEvent(new Event(Event.CHANGE));
		}
		
		public function get rectangleList():Vector.<Rectangle> 
		{
			return _rectangleList;
		}
		
	}
	
}
class SingletonBlock { };