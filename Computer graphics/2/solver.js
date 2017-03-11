'use strict';

/**
 * Created by ed on 11.03.17.
 */

class Solver {
    constructor(b) {
        this.b = b;
    }

    astroid(t) {
        let x = this.b * Math.pow(Math.cos(t), 3);
        let y = this.b * Math.pow(Math.sin(t), 3);
        return new Point(x, y);
    };

    circle(t, radius = this.b / 4) {
        let x = radius * Math.cos(t);
        let y = radius * Math.sin(t);
        return new Point(x, y);
    }

    *astroidSequence(options = {left: 0, right: 2 * Math.PI, step: 1e-2}) {
        for (let t = options.left; t < options.right; t += options.step) {
            yield this.astroid(t);
        }
    };

    *circleSequence(options = {radius: this.b / 4, centerPoint: true, step: 1e-2}) {
        for (let t = 0; t < Math.PI * 2; t += options.step) {
            yield this.circle(t, options.radius);
        }
        if (options.centerPoint) {
            yield new Point(0, 0);
        }
    }

    *allPointsSequence(options = {}) {
        yield* this.astroidSequence(options.astroid);
        yield* this.circleSequence(options.circle);
    }
}