#Manipulating branches with git

####To view **all** branches (including remotes):

git branch -a


####To create a branch which tracks a remote branch:

1. View all branches by the method above
2. Find the one you want to create a tracking branch for
3. Use _git checkout branchName_ where branchName is the remote name
4. Example using a remote branch named 'cows':

**Input**: _git branch -a_

**Output**: 

master

localBranch1

localBranch2

remotes/origin/cows

remotes/origin/anotherRemoteBranch

**Input**: _git checkout cows_

**Output**:

Branch cows set up to track remote branch cows from origin. 

Switched to a new branch 'cows'


####Creating a remote branch:

git checkout -b branchName

... edit files, add and commit ...

git push -u branchName


####Deleting a remote branch:

git push origin --delete branchName



####Merging a branch into master

1. Checkout the master branch: 

   git checkout master
   
2. Merge the branch into master: 

   git merge branchName


### Creating hardlinks in Windows ###

1. Run cmd as administrator 
2. Change directory to the location for the new link
3. To link a file...

	_mklink newLinkFileName "addressOfSourceFile"_

	Example: C:\\...\NewLocationParentFolder> mklink new.txt "C:\\...\source.txt"


4. To link an entire folder...

	_mklink /d newLinkFileName "addressOfSourceFile"_

	Example: C:\\...\NewLocationParentFolder> mklink /d newFolder "C:\\...\sourceFolder"

5. **Important!**

	If you are doing this for use with Git, **do not** create the link inside the GitHub folder on your computer.
	Git will not understand it, and will be unable to add/commit such files/folders. Instead, **link _to_ the GitHub 
	folder _from_ your desired outside location**.
	
	Examples: 

	C:\\...\NewLocationParentFolder> mklink /d newFolder "C:\\...\GitHub\yourFolder"


	C:\\...\NewLocationParentFolder> mklink newFile "C:\\...\GitHub\yourFile"
