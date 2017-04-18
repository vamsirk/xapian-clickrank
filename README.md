# xapian-clickrank
Click rank project logging : See working of this :https://www.youtube.com/watch?v=cG6Y-aqDoWc

call-script.cgi calls the letor for search and gets the results for the query fired.

click-record.cgi basically logs when an url of the results is clicked.

sample logging:

<letor:: qid:2017418164654423 query:'cool' docid:50667 docid:49919 docid:60299 docid:59166 docid:60295 docid:47621 docid:66132 docid:66629>
<uclick:: qid:2017418164654423 did:50667>
<letor:: qid:2017418164723642 query:'all' docid:58856 docid:48946 docid:65866 docid:51372 docid:50726 docid:68639 docid:57819 docid:46718 docid:57740 docid:55550>
<uclick:: qid:2017418164723642 did:48946>
<uclick:: qid:2017418164723642 did:68639>
<letor:: qid:2017418183842188 query:'call' docid:56227 docid:57832 docid:54591 docid:58098 docid:57754 docid:49980 docid:54588 docid:51623 docid:49476 docid:47634>
<uclick:: qid:2017418183842188 did:56227>
<uclick:: qid:2017418183842188 did:57754>
<letor:: qid:2017418183915237 query:'hey' docid:51894>
<uclick:: qid:2017418183915237 did:51894>
<letor:: qid:201741818457873 query:'call' docid:56227 docid:57832 docid:54591 docid:58098 docid:57754 docid:49980 docid:54588 docid:51623 docid:49476 docid:47634>
<uclick:: qid:201741818457873 did:58098>
<uclick:: qid:201741818457873 did:54588>
<letor:: qid:2017418184540133 query:'cool' docid:50667 docid:49919 docid:60299 docid:59166 docid:60295 docid:47621 docid:66132 docid:66629>
<uclick:: qid:2017418184540133 did:60299>

The docids which are displayed to the user w.r.t a query is logged and the order of the docs logged is the ranking done by letor.
uclick:: represents the document clicked by user for the query represented as qid.

The above logs have the necessary information to format them in the form of Qrel and Query file which can be used to prepare the training file.

The relevance judgments can be drawn from user clicks. For example:

 for qid:2017418183842188 user clicked did: 56227 and 57754. 
 
 The relevance judgements are rank1: 56227
                              rank2: 57754
                              rank3: 57832
                              rank4: 54591
                              rank5: 58098
