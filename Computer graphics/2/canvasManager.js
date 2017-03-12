'use strict';

/**
 * Created by ed on 11.03.17.
 */
class CanvasManager {
    constructor(canvas, options) {
        if (!options) {
            options = {}
        }

        this._canvas = canvas;
        this._offset = {x: 0, y: 0};
        this._scale = {x: 1, y: 1, center: new Point(0, 0)};
        this._rotation = {angle: 0, center: new Point(0, 0)};
    }

    set offset(options) {
        this._offset.x = options.x;
        this._offset.y = options.y;
    }

    set scale(options) {
        this._scale.x = options.x;
        this._scale.y = options.y;
        this._scale.center = options.center;
    }

    set rotation(options) {
        this._rotation.angle = options.angle;
        this._rotation.center = options.center;
    }

    get scale() {
        return {
            x: this._scale.x,
            y: this._scale.y,
            center: this._scale.center
        };
    }

    get offset() {
        return {
            x: this._offset.x,
            y: this._offset.y,
        };
    }

    get rotation() {
        return {
            angle: this._rotation.angle,
            center: this._rotation.center
        }
    }

    getMousePosition(event) {
        if (event) {
            let rect = this._canvas.getBoundingClientRect();
            return this._toVirtualCoordinates({
                x: event.clientX - rect.left,
                y: event.clientY - rect.top
            });
        } else {
            return undefined;
        }
    }

    clear() {
        let context = this._canvas.getContext('2d');
        context.clearRect(0, 0, this._canvas.width, this._canvas.height);
    }

    drawLine(p1, p2, options) {
        if (!options) {
            options = {}
        }

        p1 = this._toScreenCoordinates(p1);
        p2 = this._toScreenCoordinates(p2);

        let context = this._canvas.getContext('2d');
        context.beginPath();

        context.lineWidth = options.lineWidth || 1;
        context.strokeOpacity = options.opacity || 1;
        context.strokeStyle = options.color || 'black';

        context.moveTo(p1.x, p1.y);
        context.lineTo(p2.x, p2.y);
        context.stroke();

        context.closePath();
    }

    drawPoint(options) {
        if (!options) return false;
        if (!options.point || !(isFinite(options.point.x) && isFinite(options.point.y))) return false;

        let point = options.point;
        if (!point) return false;
        let screenPoint = this._toScreenCoordinates(point);
        let x = screenPoint.x;
        let y = screenPoint.y;
        if (!(x && y)) return false;
        let color = options.color || 'black';
        let radius = options.radius || 1;

        let context = this._canvas.getContext("2d");

        context.beginPath();
        context.fillStyle = context.strokeStyle = color;
        context.arc(x, y, radius, 0, 2 * Math.PI);
        context.fill();
        context.closePath();

        return true;
    }

    drawGrid(options) {
        if (!options) {
            options = {};
        }
        options.color = options.color || 'gray';
        options.lineWidth = options.lineWidth || 1;
        options.axisWidth = options.axisWidth || 3;
        options.axisColor = options.axisColor || 'pink';
        let step = options.step || 10;

        let top = this._toVirtualCoordinates({x: 0, y: 0});
        let bottom = this._toVirtualCoordinates({x: this._canvas.width, y: this._canvas.height});

        for (let x = Math.round(top.x / step) * step; x <= bottom.x; x += step) {
            this.drawLine(
                {x: x, y: top.y},
                {x: x, y: bottom.y},
                options
            );
        }

        for (let y = Math.round(top.y / step) * step; y <= bottom.y; y += step) {
            this.drawLine(
                {x: top.x, y: y},
                {x: bottom.x, y: y},
                options
            );
        }

        this.drawLine(
            top,
            {x: top.x, y: bottom.y},
            options
        );
        this.drawLine(
            top,
            {x: bottom.x, y: top.y},
            options
        );
        this.drawLine(
            {x: bottom.x, y: top.y},
            {x: bottom.x, y: bottom.y},
            options
        );
        this.drawLine(
            {x: top.x, y: bottom.y},
            {x: bottom.x, y: bottom.y},
            options
        );

        options.lineWidth = options.axisWidth;
        options.color = options.axisColor;
        this.drawLine(
            {x: top.x, y: 0},
            {x: bottom.x, y: 0},
            options
        );
        this.drawLine(
            {x: 0, y: top.y},
            {x: 0, y: bottom.y},
            options
        )
    }

    _toScreenCoordinates(point) {
        let result = new Point(point.x, point.y);

        // scale
        result.x = this._scale.center.x + (result.x - this._scale.center.x) * this._scale.x;
        result.y = this._scale.center.y + (result.y - this._scale.center.y) * this._scale.y;

        // rotation
        let newX = this._rotation.center.x + (result.x - this._rotation.center.x) * Math.cos(this._rotation.angle) + (result.y - this._rotation.center.y) * Math.sin(this._rotation.angle);
        let newY = this._rotation.center.y - (result.x - this._rotation.center.x) * Math.sin(this._rotation.angle) + (result.y - this._rotation.center.y) * Math.cos(this._rotation.angle);
        result.x = newX;
        result.y = newY;

        // offset
        result.x += this._offset.x;
        result.y += this._offset.y;

        console.log(point, '->', result);
        return result;
    }

    _toVirtualCoordinates(point) {
        let result = new Point(point.x, point.y);

        // offset
        result.x -= this._offset.x;
        result.y -= this._offset.y;

        // scale
        result.x = (result.x - this._scale.center.x) / this._scale.x + this._scale.center.x;
        result.y = (result.y - this._scale.center.y) / this._scale.y + this._scale.center.y;

        return result;
    }
}