function test () {
    a=$(mktemp)
    ./poker-cli sort < testdata/$1.txt > a
    if diff a testdata/$1-out.txt; then 
        echo "✅ Test $1 Passed"
    else
        echo "❌ Test $1 Failed"
    fi
    rm a
}
test straight-flush
test four-of-a-kind
test full-house
test full-house-6
test flush
test straight
test triple
test pairs-singles
