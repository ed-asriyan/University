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


}