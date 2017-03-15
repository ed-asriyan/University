'use strict';

/**
 * Created by ed on 14.03.17.
 */

const transformations = (function () {
    const move = function (point, options = {x: 0, y: 0}) {
        let x = point.x + options.x;
        let y = point.y + options.y;
        return new Point(x, y);
    };

    const scale = function (point, options = {x: 0, y: 0, center: new Point(0, 0)}) {
        let x = options.center.x + (point.x - options.center.x) * options.x;
        let y = options.center.y + (point.y - options.center.y) * options.y;
        return new Point(x, y);
    };

    const rotate = function (point, options = {angle: 0, center: new Point(0, 0)}) {
        let x = options.center.x + (point.x - options.center.x) * Math.cos(options.angle) + (point.y - options.center.y) * Math.sin(options.angle);
        let y = options.center.y - (point.x - options.center.x) * Math.sin(options.angle) + (point.y - options.center.y) * Math.cos(options.angle);
        return new Point(x, y);
    };

    return {
        move: move,
        scale: scale,
        rotate: rotate
    };
}());