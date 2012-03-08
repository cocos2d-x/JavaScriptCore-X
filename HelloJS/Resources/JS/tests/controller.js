require ('JS/tests/testResource.js');
require ('JS/tests/ActionsTest.js');

var MainMenu = {
    //FIXME: use variable to judge whether the scene is first run.
    isFirstRun  : true,
    beginPos    : new CCPoint(0, 0),
    itemMenu    : null,
    LINE_SPACE  : 40, 
    curPos      : new CCPoint(0, 0),
    testNames   : {   ActionsTest         : function()
                                            {
                                                debug.log("call back");
                                                var s = new ActionsTestScene();
                                                s.runThisTest();
                                            },
                      TransitionsTest     : function() {},
                      ProgressActionsTest : function() {},
                      EffectsTest         : function() {},
                      ClickAndMoveTest    : function() {},
                      RotateWorldTest     : function() {},
                      ParticleTest        : function() {},
                      EaseActionsTest     : function() {},
                      MotionStreakTest    : function() {},
                      DrawPrimitivesTest  : function() {},
                      CocosNodeTest       : function() {},
                      TouchesTest         : function() {},
                      MenuTest            : function() {},
                      ActionManagerTest   : function() {},
                      LayerTest           : function() {},
                      SceneTest           : function() {},
                      ParallaxTest        : function() {},
                      TileMapTest         : function() {},
                      IntervalTest        : function() {},
                      ChipmunkTest        : function() {},
                      LabelTest           : function() {},
                      TextInputTest       : function() {},
                      SpriteTest          : function() {},
                      SchdulerTest        : function() {},
                      RenderTextureTest   : function() {},
                      Texture2DTest       : function() {},
                      Box2dTest           : function() {},
                      Box2dTestBed        : function() {},
                      EffectAdvancedTest  : function() {},
                      HiResTest           : function() {},
                      Accelerometer       : function() {},
                      KeypadTest          : function() {},
	                  CocosDenshionTest   : function() {},
                      PerformanceTest     : function() {},
                      ZwoptexTest         : function() {},
	                  CurlTest            : function() {},
	                  UserDefaultTest     : function() {},
                      DirectorTest        : function() {},
                      BugsTest            : function() {},
	                  FontTest            : function() {},
	                  CurrentLanguageTest : function() {},
	                  TextureCacheTest    : function() {},
                      ExtensionsTest      : function() {}  }
};

MainMenu.start = function () {

    // add close menu
    //var closeItem = CCMenuItemImage.itemFromNormalImage(ResourcePath.COLSE, ResourcePath.CLOSE, this, this.menuCallback);
    //var menu = CCMenu::menuWithItems(closeItem, null);
    //var s = CCDirector.getWinSize();
    //menu.setPosition(new CCPoint(0, 0));
    //closeItem.setPosition(new CCPoint(s.width - 30, s.height - 30));
    var size = CCDirector.getWinSize();
    // add close menu
    var closeItem = new CCMenuItemImage(RC.s_pPathClose, RC.s_pPathClose, function(sender) {
        CCDirector.end();
    });

    var menu = new CCMenu();
    menu.addChild(closeItem);
    menu.setPosition( new CCPoint(0, 0) );
    closeItem.setPosition(new CCPoint( size.width - 30, size.height - 30));
    // add menu items for tests
    this.itemMenu = new CCMenu();
    var i = 0;
    for (var propName in this.testNames)
    {
        var label = new CCLabelTTF(propName, "Arial", 24.0);
        var menuItem = new CCMenuItemLabel(label, this.testNames[propName]);
        menuItem.setPosition(new CCPoint(size.width / 2, (size.height - ++i * this.LINE_SPACE)));
        this.itemMenu.addChild(menuItem);
    }
    
    //this.itemMenu->setContentSize();
    this.itemMenu.setPosition(this.curPos);
    
    var scene = new CCScene();
    scene.addChild(this.itemMenu);
    scene.addChild(menu, 1);
    scene.registerAsTouchHandler();
    scene.touchesBegan = function(points) {
        MainMenu.touchesBegan(points);
    };

    scene.touchesMoved = function(points) {
        MainMenu.touchesMoved(points);
    };

    if (this.isFirstRun) {
        this.isFirstRun = false;
        CCDirector.runWithScene(scene);
    } else {
        CCDirector.replaceScene(scene);
    }
};

MainMenu.touchesBegan = function(points) {
    this.beginPos = points[0];
};

MainMenu.touchesMoved = function(points) {
    var size = CCDirector.getWinSize();
    var moveY = points[0].y - this.beginPos.y;
    var pos = this.itemMenu.getPosition();
    var nextPos = new CCPoint(pos.x, pos.y + moveY);

    if (nextPos.y < 0) {
        this.itemMenu.setPosition(new CCPoint(0, 0));
        return;
    }

    if (nextPos.y > ((this.testNames.length + 1) * this.LINE_SPACE - size.height)) {
        this.itemMenu.setPosition(new CCPoint(0, (this.testNames.length + 1) * this.LINE_SPACE - size.height));
        return;
    }

    this.itemMenu.setPosition(nextPos);
    this.beginPos = points[0];
    this.curPos = nextPos;
};

