'use strict';

/**
 * Created by ed on 19.02.17.
 */

class HistoryManager {
    _clone(obj) {
        return JSON.parse(JSON.stringify(obj));
    }

    constructor(initial) {
        this._history = [this._clone(initial)];
        this._position = 0;
    }

    capture(obj) {
        return this._history[this._history.length = ++this._position] = this._clone(obj);
    }

    undo() {
        if (this._position > 0) {
            return this._clone(this._history[--this._position]);
        }
    }

    redo() {
        if (this._position + 1 < this._history.length) {
            return this._clone(this._history[++this._position]);
        }
    }

    reset() {
        this._history.length = 1;
        return this._clone(this._history[this._position = 0]);
    }

    clear() {
        return this._clone(this.capture(this._history[0]));
    }

    last() {
        return this._clone(this._history[this._history.length - 1]);
    }
}