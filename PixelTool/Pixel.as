

package  {
	import flash.display.MovieClip;
	import flash.events.MouseEvent;
	
	
	public class Pixel extends MovieClip{
		public static var clicState:Boolean = false;
		public static var clicValue:Boolean = false;
		
		public function Pixel() {
			// constructor code
			addEventListener(MouseEvent.MOUSE_DOWN, onDown)
			
			addEventListener(MouseEvent.MOUSE_OVER, onOver)
			addEventListener(MouseEvent.RIGHT_MOUSE_DOWN, onRightDown)
			
			this.width = this.height = 15
			
		}
		public var state:Boolean = false;
		
		public function update(){
			if(!this.state) this.gotoAndStop(1)
			else this.gotoAndStop(2)
		}
		private function onDown(pE: MouseEvent){
			this.state = true;
			
			update()
			
			Pixel.clicState = true;
			Pixel.clicValue = this.state
			
			this.parent.parent.addEventListener(MouseEvent.MOUSE_UP, onUp)
		}
		
		private function onRightDown(pE: MouseEvent){
			this.state = false;
			
			update()
			
			Pixel.clicState = true;
			Pixel.clicValue = this.state
			
			this.parent.parent.addEventListener(MouseEvent.MOUSE_UP, onUp)
		}
		
		private function onUp(pE: MouseEvent){
			Pixel.clicState = false;
		}
		
		private function onOver(pE: MouseEvent){
			if(Pixel.clicState){
				this.state = Pixel.clicValue
				update()
			}
		}

	}
	
}
