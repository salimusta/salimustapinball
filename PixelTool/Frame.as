package  {
	import flash.display.MovieClip;
	
	public class Frame extends MovieClip{
		private var pixelTab:Array;
		public var frameWidth;
		public var frameHeight;
		
		public function getPixelState(_x, _y){
			return pixelTab[_y][_x].state
		}
		public function setPixelState(_x, _y, _state){
			pixelTab[_y][_x].state = _state
			pixelTab[_y][_x].update()
			
		}
		public function Frame(width, height) {
			frameWidth = width;
			frameHeight = height;
			pixelTab = new Array(height);
			for(var j = 0; j < height ; j++){
				pixelTab[j] = new Array(width);
				for(var i = 0; i < width ; i++){
					var pixel = new Pixel();
					pixel.x = i * (pixel.width*1.1)
					pixel.y = j * (pixel.height*1.1) 
					addChild(pixel)
					
					pixelTab[j][i] = pixel;
				}
			}
			
			
		}

	}
	
}


		