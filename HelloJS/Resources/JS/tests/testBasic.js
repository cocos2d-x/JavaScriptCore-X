require('JS/tests/controller.js');
require('JS/tests/CCClass.js');

var TestScene = Class.extend({

  init: function(bPortrait) {
      // init our CCScene
      debug.log("TestScene init: bPortrait = "+bPortrait);
      this.__scene = new CCScene();
      this.__scene.userdata = this;
      this.__scene.onEnter =  function() {
          debug.log("test scene onEnter.");
          var that = this.userdata;
          that.onEnter();
      };

      this.__bPortrait = bPortrait;
      if (this.__bPortrait) {
          // TODO
          //CCDirector::sharedDirector()->setDeviceOrientation(CCDeviceOrientationLandscapeRight);
      }
  },

  onEnter: function() {
      debug.log("TestScene onEnter.");
      var size = CCDirector.getWinSize();
      var label = new CCLabelTTF("MainMenu", "Arial", 20);

      var menuItem = new CCMenuItemLabel(label, function () {
          debug.log("mainmenu is clicked!");
          MainMenu.start();
      });

      menuItem.setPosition(new CCPoint(size.width-50, 25));

      var menu = CCMenu.menuWithItems(menuItem);

      menu.setPosition(new CCPoint(0, 0));

      this.__scene.addChild(menu);
  },

  runThisTest: function() {
      // override this function
      debug.log("error, this function should be implemented by subclass");
  },

  getScene: function() {
      return this.__scene;
  }

});

