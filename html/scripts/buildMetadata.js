const { LeetCode, Credential } = require('leetcode-query');
const fs = require('fs');

const factory = (x) => {
    let q = [];
    for(let d of x.topicTags) {
        q.push(d.name);
    }
    return {
        [x.questionFrontendId] : {
            "Title": x.title,
            "TitleSlug": x.titleSlug,
            "Difficulty": x.difficulty,
            "Tags": q
        }
    };
};

const fn = async () => {
    let metadata = {};
    const leetcode = new LeetCode();
    try{
        for(let i=0; i<3000; i+=30) {
            const glob = await leetcode.problems({offset: i, limit:30});
            for(let x of glob.questions) {
                metadata = {...metadata, ...factory(x)};
            }
        }
    }
    catch(e) {}
    const mdata = JSON.stringify(metadata, null, 4);
    fs.writeFileSync('metadata.json', mdata, 'utf8');
};

fn();