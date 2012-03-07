require("JS/helloworld/game.js");
require("JS/helloworld/block.js");

var MainMenu = {};
MainMenu.start = function () {
	var menuScene = new CCScene();



	//var menu = new CCMenu();

	var label1 = new CCLabelTTF("Play","Chalkboard SE", 18.0);
	var label2 = new CCLabelTTF("Options","Chalkboard SE", 18.0);

	var item1 = new CCMenuItemLabel(label1, function () {
		debug.log("game will start");
		Game.start();
	});
	var item2 = new CCMenuItemLabel(label2, function () {
		debug.log("options");
	});
	item1.setPosition(new CCPoint(160, 300));
	item2.setPosition(new CCPoint(160, 150));

    //staticMenu.addChild(item1);
	//menu.addChildren(item1, item2);
    var menu = CCMenu.menuWithItems(item1, item2);

	menu.setPosition(new CCPoint(0, 0));
	menuScene.addChild(menu);

	// preload music
	CCAudioManager.preloadBackgroundMusic("music.mp3", true);

	// run the menu scene
	CCDirector.runWithScene(menuScene);
};
