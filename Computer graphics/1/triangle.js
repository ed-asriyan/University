'use strict';

/**
 * Created by ed on 04.03.17.
 */

class Triangle {
    constructor(p1, p2, p3) {
        this._a = p1;
        this._b = p2;
        this._c = p3;
    }

    get a() {
        return this._a;
    }

    get b() {
        return this._b;
    }

    get c() {
        return this._c;
    }

    get orthocenter() {
        if (!this._orthocenter) {
            this._orthocenter = Triangle.findOrthocenter(this._a, this._b, this._c);
        }
        return this._orthocenter;
    }

    get orthocenterDistance() {
        if (!this._orthocenterDistance) {
            let o = this.orthocenter;
            this._orthocenterDistance = Math.abs(o.x) + Math.abs(o.y);
        }
        return this._orthocenterDistance;
    }

    isDegenerate() {
        // points equality
        if (
            (this.a.x == this.b.x && this.a.y == this.b.y) ||
            (this.a.x == this.c.x && this.a.y == this.c.y) ||
            (this.b.x == this.c.x && this.b.y == this.c.y)
        ) {
            return true;
        }

        return false;
    }

    static findOrthocenter(p1, p2, p3) {
        let res = {};

        let a = p2.y - p1.y;
        let a1 = p2.x - p1.x;

        let ab, ab1, ab2;
        if (a != 0 && a1 != 0) {
            ab = a / a1;
            ab1 = -1 / ab;
            ab2 = (p3.y) - (ab1 * p3.x);
        }

        let b = p3.y - p2.y;
        let b1 = p3.x - p2.x;

        let bc, bc1, bc2;
        if (b != 0 && b1 != 0) {
            bc = b / b1;
            bc1 = -1 / bc;
            bc2 = (p1.y) - (bc1 * p1.x);
        }

        let c = p3.y - p1.y;
        let c1 = p3.x - p1.x;

        let ca, ca1, ca2;
        if (c != 0 && c1 != 0) {
            ca = c / c1;
            ca1 = -1 / ca;
            ca2 = (p2.y) - (ca1 * p2.x);
        }

        let con, con1, con2, con3;
        let ad, ad1, ad2, ad3;
        let di, di1;
        let y8;
        if (a != 0 && a1 != 0 && b != 0 && b1 != 0 && c != 0 && c1 != 0) {
            con = -bc1;
            con1 = -bc2;
            ad = con + ab1;
            ad1 = ab2 + con1;
            di = ad1 / ad;
            di1 = -di;
            y8 = (bc1 * di1) + bc2;

            if (Math.round(di1) == (di1) && Math.round(y8) == (y8)) {
                res.x = di1;
                res.y = y8;
            } else if (Math.round(di1) != (di1) && Math.round(y8) == (y8)) {
                res.x = di1.toFixed(5);
                res.y = y8;
            } else if (Math.round(di1) == (di1) && Math.round(y8) != (y8)) {
                res.x = di1;
                res.y = y8.toFixed(5);
            } else if (Math.round(di1) != (di1) && Math.round(y8) != (y8)) {
                res.x = di1.toFixed(5);
                res.y = y8.toFixed(5);
            }
        } else if (a != 0 && a1 != 0 && b != 0 && b1 != 0) {
            con = -bc1;
            con1 = -bc2;
            ad = con + ab1;
            ad1 = ab2 + con1;
            di = ad1 / ad;
            di1 = -di;
            y8 = (bc1 * di1) + bc2;

            if (Math.round(di1) == (di1) && Math.round(y8) == (y8)) {
                res.x = di1;
                res.y = y8;
            } else if (Math.round(di1) != (di1) && Math.round(y8) == (y8)) {
                res.x = di1.toFixed(5);
                res.y = y8;
            } else if (Math.round(di1) == (di1) && Math.round(y8) != (y8)) {
                res.x = di1;
                res.y = y8.toFixed(5);
            } else if (Math.round(di1) != (di1) && Math.round(y8) != (y8)) {
                res.x = di1.toFixed(5);
                res.y = y8.toFixed(5);
            }
        } else if (b != 0 && b1 != 0 && c != 0 && c1 != 0) {
            con2 = -ca1;
            con3 = -ca2;
            ad2 = con2 + bc1;
            ad3 = bc2 + con3;
            di = ad3 / ad2;
            di1 = -di;
            y8 = (ca1 * di1) + ca2;

            if (Math.round(di1) == (di1) && Math.round(y8) == (y8)) {
                res.x = di1;
                res.y = y8;
            } else if (Math.round(di1) != (di1) && Math.round(y8) == (y8)) {
                res.x = di1.toFixed(5);
                res.y = y8;
            } else if (Math.round(di1) == (di1) && Math.round(y8) != (y8)) {
                res.x = di1;
                res.y = y8.toFixed(5);
            } else if (Math.round(di1) != (di1) && Math.round(y8) != (y8)) {
                res.x = di1.toFixed(5);
                res.y = y8.toFixed(5);
            }
        } else if (a != 0 && a1 != 0 && c != 0 && c1 != 0) {
            con2 = -ab1;
            con3 = -ab2;
            ad2 = con2 + ca1;
            ad3 = ca2 + con3;
            di = ad3 / ad2;
            di1 = -di;
            y8 = (ab1 * di1) + ab2;

            if (Math.round(di1) == (di1) && Math.round(y8) == (y8)) {
                res.x = di1;
                res.y = y8;
            } else if (Math.round(di1) != (di1) && Math.round(y8) == (y8)) {
                res.x = di1.toFixed(5);
                res.y = y8;
            } else if (Math.round(di1) == (di1) && Math.round(y8) != (y8)) {
                res.x = di1;
                res.y = y8.toFixed(5);
            } else if (Math.round(di1) != (di1) && Math.round(y8) != (y8)) {
                res.x = di1.toFixed(5);
                res.y = y8.toFixed(5);
            }
        }

        if (isFinite(res.x) && isFinite(res.y)) {
            return res;
        } else {
            return undefined;
        }
    };

    static fromPoints(points) {
        let triangles = [];
        for (let i = 0; i < points.length; ++i) {
            for (let j = i + 1; j < points.length; ++j) {
                for (let k = j + 1; k < points.length; ++k) {
                    let a = points[i];
                    let b = points[j];
                    let c = points[k];

                    let triangle = new Triangle(a, b, c);
                    if (!triangle.isDegenerate()) {
                        triangles.push(triangle);
                    }
                }
            }
        }
        return triangles;
    };

    static compare(a, b) {
        let number = a.orthocenterDistance - b.orthocenterDistance;
        return number ? number < 0 ? -1 : 1 : 0
    }
}