'use strict';

/**
 * Created by ed on 04.03.17.
 */

class Point {
    constructor(x, y) {
        this.x = x;
        this.y = y;
    }

    static equals(a, b) {
        return a.x == b.x && a.y == b.y;
    }

    static compare(a, b) {
        let number = Math.abs(a.x) + Math.abs(a.y) - Math.abs(b.x) - Math.abs(a.y);
        return number < 0 ? number ? -1 : 0 : 1;
    }

}