'use strict';

/**
 * Created by ed on 19.02.17.
 */

class HistoryManager {
    constructor(initial) {
        this._history = [initial];
        this._position = 0;
    }

    capture(obj) {
        return this._history[this._history.length = ++this._position] = obj;
    }

    undo() {
        if (this._position > 0) {
            return this._history[--this._position];
        }
    }

    redo() {
        if (this._position + 1 < this._history.length) {
            return this._history[++this._position];
        }
    }

    reset() {
        this._history.length = 1;
        return this._history[this._position = 0];
    }

    clear() {
        return this.capture(this._history[0]);
    }
}