/*
// HTML Code Reference
// Navbar
<li class="nav-item">
<a href="#category-{}" class="nav-link">
<span class="nav-link-text">

</span>
</a>
</li>

// Contents to be shown
<div class="primary-category" id="category-{id}">
    <div class="category-div">
        <label class="category-title">{title}</label>
    </div>
    <ul class="accordion" id="accordion${id}">
        <li class="question" id="ID${id}">
            <input type="checkbox" name="quest" id="q${id}" onclick="toggleQuestion(this) />
            <label class="question-title" for="q${id}">
            ${title}
            </label>
            <div class="code-content">
                <div class="editor-container">
                    <div id="editor-${id}">

                    </div>
                </div>
            </div>
        </li>
    </ul>
</div>
*/

/**
 * @typedef {Object} Question
 * @typedef {Object} Category
 *
 * @property {Object<Question>} questions
 * @property {Object<Category>} categories
 * @property {Set<String>} openedQuestions
 * @property {string} theme
 * @property {string} pathPrefix
 * @property {string} mostRecent
 */

let questions = {};
let categories = {};
let openedQuestions = new Set();
const theme = ["chaos", "xcode"][
    window.matchMedia("(prefers-color-scheme: light)").matches ? 1 : 0
];
let pathPrefix = "";
let mostRecent = "";

/**
 * Creates a category entry HTML
 *
 * @param {string} id
 * @param {string} title
 * @returns {string}
 */

function makeCategory(id, title) {
    return `
    <div class="primary-category" id="category-${id}">
    <div class="category-div">
    <label class="category-title">${title}</label>
    </div>
    <ul class="accordion" id="accordion${id}">
    </ul>
    </div>
    `;
}

/**
 * Creates a navbar entry HTML
 *
 * @param {string} id
 * @param {string} title
 * @returns {string}
 */

function makeNavbar(id, title) {
    return `
    <li class="nav-item">
        <a href="#category-${id}" class="nav-link">
            <span class="nav-link-text">
                ${title}
            </span>
        </a>
    </li>
    `;
}

/**
 * Creates a question entry HTML
 *
 * @param {string} id
 * @param {string} title
 * @returns {string}
 */

function makeQuestion(id, title) {
    return `
    <li class="question" id="ID-${id}">
        <input type="checkbox" name="quest" id="q${id}" onclick="toggleQuestion(this)" />
        <label class="question-title" for="q${id}">
            ${id}. ${title}
        </label>
        <div class="code-content">
            <div class="editor-container">
                <div class="editor-contents" id="editor-${id}">
                Loading...<br /> This will be done in a few seconds.<br />
                If you're seeing this for a long time something went wrong or poor connectivity!
                </div>
            </div>
        </div>
    </li>
    `;
}

/**
 * Load the questions and categories on DOM load
 * Also load the editor
 *
 * @returns {void}
 */

document.addEventListener("DOMContentLoaded", async () => {
    questions = await loadQuestions();
    categories = getCategories(questions);

    createCategories();
    createQuestions();
});

/**
 * Load the questions from local source
 * 
 * This is what a single question looks like:
 * 
 * "id": {
        "Difficulty": "string",
        "Tags": [
            "string", "string", ....
        ],
        "Title": "string",
        "TitleSlug": "string",
        "URI": "./<category>/<filename>.cpp"
    }
 *
 * @returns {Promise<Questions>}
 */

async function loadQuestions() {
    let response = await fetch("/URIs.json");
    if (!response.ok) {
        pathPrefix = "/DP/";
        response = await fetch(pathPrefix + "URIs.json");
        if (!response.ok) throw new Error("Network response was not ok");
    }

    const jsonData = await response.json(); // Extract JSON data from the response
    return jsonData;
}

/**
 * Gets the categories from the questions
 * Categories are the parent folders of the files
 *
 * This is what the return looks like:
 * {
 *   "category1": 0,
 *   "category2": 1,
 *   ....
 * }
 *
 *
 * @param {Object<Question>} questions
 * @returns {Object<Category>}
 */

function getCategories(questions) {
    let st = new Set();
    for (let key in questions) {
        if (key === "NLC" || key === "built on") continue;
        st.add(questions[key]["URI"].split("/")[1]);
    }
    let obj = {};
    let idx = 0;

    for (let category of st) {
        obj[category] = String(idx++);
    }

    return obj;
}

/**
 * Creates the categories on the DOM
 *
 * @returns {void}
 */

function createCategories() {
    let html = "",
        nv = "";
    for (let category in categories) {
        let c = ((str) => str.charAt(0).toUpperCase() + str.slice(1))(category);
        html += makeCategory(categories[category], c);
        nv += makeNavbar(categories[category], c);
    }
    document.getElementById("navbar").innerHTML += nv;
    document.getElementById("main-content").innerHTML += html;
}

/**
 * Creates the questions on the DOM
 *
 * @returns {void}
 */

function createQuestions() {
    let arr = [];
    for (let key in questions) {
        if (key !== "NLC" && key !== "built on") arr.push(key);
    }
    arr.sort((a, b) => Number(a) - Number(b));
    for (let key of arr) {
        let category = questions[key]["URI"].split("/")[1];
        let title = questions[key]["Title"];
        let html = makeQuestion(key, title);
        document.getElementById(`accordion${categories[category]}`).innerHTML +=
            html;
    }
}

/**
 * Toggles the visibility of an accordion list item.
 *
 * @param {HTMLElement} obj
 * @returns {void}
 */

function toggleQuestion(obj) {
    let id = obj.id.slice(1);
    if (!openedQuestions.has(id)) {
        getCode(id).then((code) => setupEditor(id, code));
    }
    mostRecent = id;
}

/**
 * Setup the Ace editor
 *
 * @param {string} id
 * @param {string} code
 * @returns {void}
 */

function setupEditor(id, code) {
    let editor = ace.edit(`editor-${id}`);
    editor.setTheme(`ace/theme/${theme}`);
    editor.session.setMode("ace/mode/c_cpp");
    editor.session.setValue(code + "\n");
    openedQuestions[id] = editor;
    editor.setOption("readOnly", true);

    // Wrap text
    editor.session.setUseWrapMode(true);

    // Overscroll half
    editor.setOption("scrollPastEnd", 0.3);

    // Disable print margin
    editor.setShowPrintMargin(false);

    // Scroll down to opened content
    let element = document.getElementById(`editor-${id}`);
    if (element) {
        element.scrollIntoView({ behavior: "smooth", block: "start" });
    }
}

/**
 * Get the code from the URI
 *
 * @param {string} id
 * @returns {string}
 */

function getCode(id) {
    let uri = questions[id]["URI"];
    if (pathPrefix !== "") uri = pathPrefix + uri.slice(1);
    return fetch(uri).then((res) => res.text());
}
