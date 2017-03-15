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
        let aX = this.b.x - this.a.x;
        let aY = this.b.y - this.a.y;

        let cX = this.c.x - this.a.x;
        let cY = this.c.y - this.a.y;

        return aX * cY == aY * cX;
    }

    static findOrthocenter(p1, p2, p3) {
        let res = {};

        let aX = p2.x - p1.x;
        let aY = p2.y - p1.y;

        let aTan = -aX / aY;
        let ab2 = (p3.y) - (aTan * p3.x);


        let bX = p3.x - p2.x;
        let bY = p3.y - p2.y;

        let bTan = -bX / bY;
        let bc2 = (p1.y) - (bTan * p1.x);


        let cX = p3.x - p1.x;
        let cY = p3.y - p1.y;

        let cTan = -cX / cY;
        let ca2 = (p2.y) - (cTan * p2.x);


        let con, con1, con2, con3;
        let ad, ad1, ad2, ad3;
        let di, di1;
        let y8;
        if (aY != 0 && aX != 0 && bY != 0 && bX != 0 && cY != 0 && cX != 0) {
            con = -bTan;
            con1 = -bc2;
            ad = con + aTan;
            ad1 = ab2 + con1;
            di = ad1 / ad;
            di1 = -di;
            y8 = (bTan * di1) + bc2;

            res.x = di1;
            res.y = y8;
        } else if (aY != 0 && aX != 0 && bY != 0 && bX != 0) {
            con = -bTan;
            con1 = -bc2;
            ad = con + aTan;
            ad1 = ab2 + con1;
            di = ad1 / ad;
            di1 = -di;
            y8 = (bTan * di1) + bc2;

            res.x = di1;
            res.y = y8;
        } else if (bY != 0 && bX != 0 && cY != 0 && cX != 0) {
            con2 = -cTan;
            con3 = -ca2;
            ad2 = con2 + bTan;
            ad3 = bc2 + con3;
            di = ad3 / ad2;
            di1 = -di;
            y8 = (cTan * di1) + ca2;

            res.x = di1;
            res.y = y8;
        } else if (aY != 0 && aX != 0 && cY != 0 && cX != 0) {
            con2 = -aTan;
            con3 = -ab2;
            ad2 = con2 + cTan;
            ad3 = ca2 + con3;
            di = ad3 / ad2;
            di1 = -di;
            y8 = (aTan * di1) + ab2;

            res.x = di1;
            res.y = y8;
        } else if (aY != 0 && aX != 0) {
            res = p3;
        } else if (bY != 0 && bX != 0) {
            res = p1;
        } else if (cY != 0 && cX != 0) {
            res = p2;
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