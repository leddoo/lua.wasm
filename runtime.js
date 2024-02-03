
let c_memory;
let c_call_indirect_2;
let c_malloc;
let c_push_string;
let c_push_number;
let c_push_boolean;
let c_push_nil;
let c_do_string;
let c_on_event;
let c_resume;

const root = document.getElementById("root");
root.$$lua_id = 1;

const js_values = {
    0: null,
    1: root,
    2: null,
};
g_js_values = js_values;

let ret_val;

const text_decoder = new TextDecoder();
const text_encoder = new TextEncoder();

const clone_template_stack = [];


const dbg_log = 0==1 ? console.log : () => {};

const imports = {
    "env": {
        "js_unimplemented": () => {
            throw "unimplemented";
        },

        "js_try_2": (f, a1, a2) => {
            try {
                c_call_indirect_2(f, a1, a2);
            }
            catch(e) {
                if(e !== null) {
                    throw e;
                }
            }
        },

        "js_throw": () => {
            throw null;
        },

        "js_write_string": (s, len) => {
            const array = new Uint8Array(c_memory.buffer, s, len);
            const string = text_decoder.decode(array);
            document.getElementById("output").appendChild(document.createTextNode(string));
        },

        "js_delete_value": (id) => {
            dbg_log("delete_value", id)
            delete js_values[id];
        },

        "js_alloc_string": (dst, ptr, len) => {
            const array = new Uint8Array(c_memory.buffer, ptr, len);
            const string = text_decoder.decode(array);
            dbg_log("alloc_string", dst, string)
            js_values[dst] = string;
        },

        "js_create_element": (dst, kind, kind_len) => {
            const array = new Uint8Array(c_memory.buffer, kind, kind_len);
            const kind_str = text_decoder.decode(array);
            dbg_log("create_element", dst, kind_str)
            const node = document.createElement(kind_str);
            node.$$lua_id = dst;
            js_values[dst] = node;
        },

        "js_create_text_node": (dst, value, value_len) => {
            const array = new Uint8Array(c_memory.buffer, value, value_len);
            const value_str = text_decoder.decode(array);
            dbg_log("create_text_node", dst, value_str)
            const node = document.createTextNode(value_str);
            node.$$lua_id = dst;
            js_values[dst] = node;
        },

        "js_insert_before": (parent, node, ref) => {
            dbg_log("insert_before", js_values[parent], js_values[node], js_values[ref])
            js_values[parent].insertBefore(js_values[node], js_values[ref]);
        },

        "js_replace_node": (node, with_) => {
            dbg_log("replace_node", js_values[node], js_values[with_]);
            js_values[node].replaceWith(js_values[with_]);
        },

        "js_remove_node": (node) => {
            dbg_log("remove_node", js_values[node]);
            js_values[node].remove();
        },

        "js_set_data": (id, value, value_len) => {
            const array = new Uint8Array(c_memory.buffer, value, value_len);
            const value_str = text_decoder.decode(array);
            dbg_log("set_data", id, value_str)
            js_values[id].data = value_str;
        },

        "js_set_prop_string": (id, key, key_len, value, value_len) => {
            const key_array = new Uint8Array(c_memory.buffer, key, key_len);
            const key_str = text_decoder.decode(key_array);
            const value_array = new Uint8Array(c_memory.buffer, value, value_len);
            const value_str = text_decoder.decode(value_array);
            dbg_log("set_prop", id, key_str, value_str)
            js_values[id][key_str] = value_str;
        },

        "js_set_propk_string": (id, key, value, value_len) => {
            const value_array = new Uint8Array(c_memory.buffer, value, value_len);
            const value_str = text_decoder.decode(value_array);
            const key_str = js_values[key];
            dbg_log("set_propk", id, key_str, value_str)
            js_values[id][key_str] = value_str;
        },

        "js_push_prop": (L, dst, id, key, key_len) => {
            const key_array = new Uint8Array(c_memory.buffer, key, key_len);
            const key_str = text_decoder.decode(key_array);
            const value = js_values[id][key_str];
            dbg_log("push_prop", id, key_str, value)
            return push_value(L, dst, value);
        },

        "js_set_attr_string": (id, key, key_len, value, value_len) => {
            const key_array = new Uint8Array(c_memory.buffer, key, key_len);
            const key_str = text_decoder.decode(key_array);
            const value_array = new Uint8Array(c_memory.buffer, value, value_len);
            const value_str = text_decoder.decode(value_array);
            dbg_log("set_attr", id, key_str, value_str)
            js_values[id].setAttribute(key_str, value_str);
        },

        "js_set_attr_number": (id, key, key_len, value) => {
            const key_array = new Uint8Array(c_memory.buffer, key, key_len);
            const key_str = text_decoder.decode(key_array);
            dbg_log("set_attr", id, key_str, value)
            js_values[id].setAttribute(key_str, value);
        },

        "js_del_attr": (id, key, key_len) => {
            const key_array = new Uint8Array(c_memory.buffer, key, key_len);
            const key_str = text_decoder.decode(key_array);
            dbg_log("del_attr", id, key_str)
            js_values[id].removeAttribute(key_str);
        },

        "js_push_attr": (L, id, key, key_len) => {
            const key_array = new Uint8Array(c_memory.buffer, key, key_len);
            const key_str = text_decoder.decode(key_array);
            const value = js_values[id].getAttribute(key_str);
            dbg_log("push_attr", id, key_str, value)
            if(value === null) { c_push_nil(L); }
            else               { push_string(L, value); }
        },

        "js_first_child": (dst, node) => {
            dbg_log("first_child", dst, js_values[node])
            const child = js_values[node].firstChild;
            if(child) {
                if(child.$$lua_id) {
                    throw "todo";
                }
                child.$$lua_id = dst;
            }
            js_values[dst] = child;
        },

        "js_next_sibling": (dst, node) => {
            dbg_log("next_sibling", dst, js_values[node])
            const sibling = js_values[node].nextSibling;
            if(sibling) {
                if(sibling.$$lua_id) {
                    throw "todo";
                }
                sibling.$$lua_id = dst;
            }
            js_values[dst] = sibling;
        },

        "js_create_template": (dst, html, html_len, elems, elems_len) => {
            const html_array = new Uint8Array(c_memory.buffer, html, html_len);
            const html_str = text_decoder.decode(html_array);
            const elems_array = new Uint8Array(c_memory.buffer, elems, elems_len);
            const elems_str = text_decoder.decode(elems_array);
            dbg_log("create_template", dst, html_str, elems_str);

            const ops = elems_str.split("").map(ch => {
                if(ch == "c") { return 0; }
                if(ch == "n") { return 1; }
                if(ch == "p") { return 2; }
                if(ch == "s") { return 3; }
                throw "unreachable";
            });

            const create = () => {
                const tmpl = document.createElement("template");
                tmpl.innerHTML = html_str;
                return tmpl.content.firstChild;
            };

            let node;
            const clone = (first) => {
                node = node || create();
                const root = node.cloneNode(true);

                const s = clone_template_stack;
                s.length = 0;
                let id = first;
                let top = root;
                for(const op of ops) {
                    switch(op) {
                        case 0: {
                            s.push(top);
                            top = top.firstChild;
                        } break;

                        case 1: {
                            top = top.nextSibling;
                        } break;

                        case 2: {
                            top = s.pop();
                        } break;

                        case 3: {
                            js_values[id] = top;
                            top.$$lua_id = id;
                            id += 1;
                        } break;
                    }
                }
            };

            js_values[dst] = clone;
        },

        "js_call_i_v": (func, arg0) => {
            dbg_log("call_i_v", func, arg0)
            js_values[func](arg0);
        },

        "js_call_method": (L, dst, obj, name_ptr, name_len) => {
            const name = text_decoder.decode(new Uint8Array(c_memory.buffer, name_ptr, name_len));
            dbg_log("call", obj, name)
            const result = js_values[obj][name]();
            return push_value(L, dst, result);
        },

        "js_set_ret_string": (ptr, len) => {
            const array = new Uint8Array(c_memory.buffer, ptr, len);
            const string = text_decoder.decode(array);
            ret_val = string;
        },

        "js_delegate_event": (name_ptr, name_len) => {
            const name = text_decoder.decode(new Uint8Array(c_memory.buffer, name_ptr, name_len));
            root.addEventListener(name, async function(e) {
                const lua_id = e.target.$$lua_id;
                if(lua_id !== undefined) {
                    js_values[2] = e;
                    await run_to_completion(c_on_event(name_ptr, name_len, lua_id));
                }
            });
        },

        "js_copy_value": (dst, src) => {
            js_values[dst] = js_values[src];
        }
    },
};

async function run_to_completion(status) {
    while(status > 0) {
        dbg_log("status", status);
        if(status == 10) {
            dbg_log("fetch", ret_val);
            const result = await fetch(ret_val);
            if(result.status == 200) {
                const text = await result.text();
                push_string(0, text);
                status = c_resume(status, 1);
            }
            else {
                status = c_resume(status, 0);
            }
        }
        else {
            throw "todo";
        }
    }
    dbg_log("done", status);
}

function push_string(L, string) {
    const bytes = text_encoder.encode(string);
    const len = bytes.byteLength;
    const ptr = c_malloc(len);
    const buffer = new Uint8Array(c_memory.buffer, ptr, len);
    buffer.set(bytes);
    c_push_string(L, ptr, len);
}

function push_value(L, dst, value) {
    const t = typeof(value);
    if(t === "string")       { push_string(L, value); }
    else if(t === "number")  { c_push_number(L, value); }
    else if(t === "boolean") { c_push_boolean(L, value); }
    else if(value == null)   { c_push_nil(L); }
    else if(t === "object" || t == "function") {
        js_values[dst] = value;
        return true;
    }
    else { throw "unreachable"; }
}

async function do_string(code) {
    const bytes = text_encoder.encode(code);
    const ptr = c_malloc(bytes.byteLength + 1);
    const buffer = new Uint8Array(c_memory.buffer, ptr, bytes.byteLength + 1);
    buffer.set(bytes);
    buffer[bytes.byteLength] = 0;

    await run_to_completion(c_do_string(ptr));
}

(async function() {
    let obj = await WebAssembly.instantiateStreaming(fetch("main.wasm"), imports);
    let exports = obj.instance.exports;
    c_memory = exports.memory;
    c_call_indirect_2 = exports.c_call_indirect_2;
    c_malloc = exports.malloc;
    c_push_string = exports.push_string;
    c_push_number = exports.push_number;
    c_push_boolean = exports.push_boolean;
    c_push_nil = exports.push_nil;
    c_do_string = exports.do_string;
    c_on_event = exports.on_event;
    c_resume = exports.resume;

    exports._start();

    await do_string(await fetch("init.lua").then(code => code.text()));
    //await do_string("require 'playground'");
    await do_string("require 'plots'");
})();

