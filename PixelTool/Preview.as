package  {
	import flash.display.MovieClip;
	import flash.events.MouseEvent;

	public class Preview  extends MovieClip{
		private var main:Object = null
		public function Preview(_main:Object){
			// constructor code
			this.buttonMode = true
			main = _main;
			this.addEventListener(MouseEvent.CLICK, onClic)
			this.gotoAndStop(1)
			this.frameNumber.mouseEnabled = false
								 
		}
		
		private function onClic(pE:MouseEvent){
			main.selectFrame(Number(this.frameNumber.text)-1)
		}
		
		public function update(index){
			if( index == Number(this.frameNumber.text)-1 ) this.gotoAndStop(2)
			else this.gotoAndStop(1)
		}

	}
	
}
