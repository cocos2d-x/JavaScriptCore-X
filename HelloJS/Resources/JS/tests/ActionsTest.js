require('JS/tests/testResource.js');
require('JS/tests/controller.js');
require('JS/tests/testBasic.js');
require('JS/tests/CCClass.js');

var ActionsDemoLayer = Class.extend({
    _layer: null,
    _grossini: null,
    _tamara: null,
    _kathia: null,

    init: function() {
        this._layer = new CCNode();
        this._layer.userdata = this;
        this._layer.onEnter = function() {
            var that = this.userdata;
            that.onEnter();
        };
    },

    onEnter: function() {
        var s = CCDirector.getWinSize();
        this._grossini = new CCSprite(RC.s_pPathGrossini);
        this._tamara = new CCSprite(RC.s_pPathSister1);
        this._kathia = new CCSprite(RC.s_pPathSister2);
        this._layer.addChild(this._grossini, 1);
        this._layer.addChild(this._tamara, 2);
        this._layer.addChild(this._kathia, 3);

        this._grossini.setPosition(new CCPoint(s.width/2, s.height/3));
        this._tamara.setPosition(new CCPoint(s.width/2, 2*s.height/3));
        this._kathia.setPosition(new CCPoint(s.width/2, s.height/2));

        var label = new CCLabelTTF(this.title(), "Arial", 18.0);
        this._layer.addChild(label, 1);
        label.setPosition(new CCPoint(s.width/2, s.height-30));

        if (this.subtitle() && this.subtitle().length > 0)
        {
            var l = new CCLabelTTF(this.subtitle(), "Thonburi", 22);
            this._layer.addChild(l, 1);
            l.setPosition(new CCPoint(s.width/2, s.height-60));
        }

        // add menu
        debug.log("add menu.....");
        var item1 = new CCMenuItemImage(RC.s_pPathB1, RC.s_pPathB2, this.backCallback);
        var item2 = new CCMenuItemImage(RC.s_pPathR1, RC.s_pPathR2, this.restartCallback);
        var item3 = new CCMenuItemImage(RC.s_pPathF1, RC.s_pPathF2, this.nextCallback);

        var menu = new CCMenu(item1, item2, item3);

        menu.setPosition( new CCPoint(0, 0) );
        item1.setPosition( new CCPoint( s.width/2 - 100,30) );
        item2.setPosition( new CCPoint( s.width/2, 30) );
        item3.setPosition( new CCPoint( s.width/2 + 100,30) );

        this._layer.addChild(menu, 1);
        debug.log("ActionsDemoLayer onEnter finish.")
    },

    nextCallback: function(sender) {
        var s = new ActionsTestScene();
        s.getScene().addChild(NS_AT.nextAction());
        CCDirector.replaceScene(s.getScene());
    },

    backCallback: function(sender) {
        var s = new ActionsTestScene();
        s.getScene().addChild(NS_AT.backAction());
        CCDirector.replaceScene(s.getScene());
    },

    restartCallback: function(sender) {
        var s = new ActionsTestScene();
        s.getScene().addChild(NS_AT.restartAction());
        CCDirector.replaceScene(s.getScene());
    },

    centerSprites: function(numberOfSprites) {
        var s = CCDirector.getWinSize();

        if( numberOfSprites == 1 )
        {
            this._tamara.setIsVisible(false);
            this._kathia.setIsVisible(false);
            this._grossini.setPosition(new CCPoint(s.width/2, s.height/2));
        }
        else if( numberOfSprites == 2 )
        {
            this._kathia.setPosition( new CCPoint(s.width/3, s.height/2));
            this._tamara.setPosition( new CCPoint(2*s.width/3, s.height/2));
            this._grossini.setIsVisible(false);
        }
        else if( numberOfSprites == 3 )
        {
            this._grossini.setPosition( new CCPoint(s.width/2, s.height/2));
            this._tamara.setPosition( new CCPoint(s.width/4, s.height/2));
            this._kathia.setPosition( new CCPoint(3 * s.width/4, s.height/2));
        }
    },

    alignSpritesLeft: function(numberOfSprites) {

    },

    title: function() {
        return "ActionsTest";
    },

    subtitle: function() {
        // override this funciton to set subtitle
        return null;
    },

    getLayer: function() {
        return this._layer;
    }
});

var ActionManual = ActionsDemoLayer.extend({
    onEnter: function() {
        this._super();
        var s = CCDirector.getWinSize();
        this._tamara.setScaleX(2.5);
        this._tamara.setScaleY(-1.0);
        this._tamara.setPosition(new CCPoint(100, 70));
        this._tamara.setOpacity( 128);

        this._grossini.setRotation( 120);
        this._grossini.setPosition( new CCPoint(s.width/2, s.height/2));
        this._grossini.setColor( new CCColor( 255,0,0));

        this._kathia.setPosition( new CCPoint(s.width-100, s.height/2));
        this._kathia.setColor( new CCColor( 0,0,255));
    },
    subtitle: function() {
        return "ActionManual";
    }
});

var ActionMove = ActionsDemoLayer.extend({
    onEnter: function() {
        this._super();
        this.centerSprites(3);
        var s = CCDirector.getWinSize();

        var actionTo = new CCMoveTo(2, new CCPoint(s.width-40, s.height-40));
        var actionBy = new CCMoveBy(2, new CCPoint(80,80));
        // FIXME: reverse method wasn't exported to js.
        // var actionByBack = actionBy.reverse();

        this._tamara.runAction( actionTo);
        this._grossini.runAction( CCSequence.actions(actionBy/* , actionByBack*/));
        this._kathia.runAction( new CCMoveTo(1, CCPointMake(40,40)));

    },
    subtitle: function() {
        return "ActionMove";
    }
});

var NS_AT = {

    nActionIdx: -1,

    ActionArray: [
        function() { return new ActionManual()},
        function() { return new ActionMove()}
    ],

    nextAction: function() {
        this.nActionIdx++;
        this.nActionIdx = this.nActionIdx % this.ActionArray.length;
        debug.log("index = "+this.nActionIdx);
        return this.createLayer();
    },

    backAction: function() {
        this.nActionIdx--;
        if (this.nActionIdx < 0) this.nActionIdx += this.ActionArray.length;
        debug.log("index = "+this.nActionIdx);
        return this.createLayer();
    },

    restartAction: function() {
        return this.createLayer();
    },

    createLayer: function() {
        return this.ActionArray[this.nActionIdx]().getLayer();
    }
};

var ActionsTestScene = TestScene.extend({
    runThisTest: function() {
        NS_AT.nActionIdx = -1;
        var s = this.getScene();
        s.addChild(NS_AT.nextAction());
        CCDirector.replaceScene(s);
    }
});

