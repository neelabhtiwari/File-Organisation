#include<bits/stdc++.h>
using namespace std;

class Node{
public:
  int RecId;
  int ValidBit;
  int StartIndex;
  int RecSize;
};

class Page{
public:
  int PageSize;
  vector<Node> DirStructure;
  Page* Next;
  Page* Prev;
  Page(int size){
    PageSize=size;
    DirStructure.clear();
    Next=NULL;
    Prev=NULL;
  }
  int insert(int rid,int rsize);
  void displaypage();
  int search(int rid,int* ploc);
  int deleterecord(int rid,int* ploc);
};

int Page::insert(int rid,int rsize){
  if(DirStructure.size()==0){
    Node dir;
    dir.RecId=rid; dir.ValidBit=1; dir.StartIndex=0; dir.RecSize=rsize;
    DirStructure.push_back(dir);
    return 1;
  }
  else{
    for(int i=0;i<DirStructure.size();i++){
      if(DirStructure[i].ValidBit==1){
        if(i<DirStructure.size()-1 && rsize<=(DirStructure[i+1].StartIndex-(DirStructure[i].StartIndex+DirStructure[i].RecSize))){
          Node NewRec; NewRec.RecId=rid; NewRec.ValidBit=1; NewRec.StartIndex=(DirStructure[i].StartIndex+DirStructure[i].RecSize); NewRec.RecSize=rsize;
          DirStructure.insert(DirStructure.begin()+i+1,NewRec);
          return 1;
        }
        else if(i==DirStructure.size()-1){
          if(rsize<=PageSize-(DirStructure[i].StartIndex+DirStructure[i].RecSize)){
            Node NewRec; NewRec.RecId=rid; NewRec.ValidBit=1; NewRec.StartIndex=(DirStructure[i].StartIndex+DirStructure[i].RecSize); NewRec.RecSize=rsize;
            DirStructure.insert(DirStructure.begin()+i+1,NewRec);
            return 1;
          }
        }
      }
      else{
        if(rsize<=DirStructure[i].RecSize){
          DirStructure[i].RecId=rid; DirStructure[i].ValidBit=1; DirStructure[i].RecSize=rsize;
          return 1;
        }
      }
    }
    return 0;
  }
}

int Page::search(int rid,int* ploc){
  for(int i=0;i<DirStructure.size();i++){
    if(DirStructure[i].RecId==rid && DirStructure[i].ValidBit==1){
      *ploc=DirStructure[i].StartIndex;
      return 1;
    }
  }
  return 0;
}

void Page::displaypage(){
  if(DirStructure.size()==0){
    cout<<"Page is Empty"<<endl;
    return;
  }
  for(int i=0;i<DirStructure.size();i++){
    cout<<"Record ID - "<<DirStructure[i].RecId<<" Valid - "<<DirStructure[i].ValidBit<<" Start Index - "<<DirStructure[i].StartIndex<<" Size - "<<DirStructure[i].RecSize<<endl;
  }
  cout<<endl<<endl;
  return;
}


int Page::deleterecord(int rid,int* ploc){
  for(int i=0;i<DirStructure.size();i++){
    if(DirStructure[i].RecId==rid && DirStructure[i].ValidBit==1){
      *ploc=DirStructure[i].StartIndex;
      DirStructure[i].ValidBit=0;
      if(i<DirStructure.size()-1 && DirStructure[i+1].StartIndex-(DirStructure[i].StartIndex+DirStructure[i].RecSize)!=0){
        DirStructure[i].RecSize=DirStructure[i+1].StartIndex-DirStructure[i].StartIndex;
      }
      return 1;
    }
  }
  return 0;
}

class Disk{
public:
  Page* FileStart;
  Disk(){
    FileStart=NULL;
  }
  void displaydisk();
};

void Disk::displaydisk(){
  if(FileStart==NULL){
    cout<<"No page present in the disk"<<endl<<endl;
    return;
  }
  int pno=1;
  Page* temp=FileStart;
  while(temp!=NULL){
    cout<<"Page Number - "<<pno++<<endl<<endl;
    temp->displaypage();
    temp=temp->Next;
  }
  return;
}


int main(){
  cout<<"Give Size of Page ";
  int ps;
  cin>>ps;

  Disk DiskContent;
  Page* FirstPage=NULL;
  Page* LastPage=NULL;

  while(1){
    cout<<"Give 1 to insert a number, 2 to search a record, 3 to delete a record, 4 to display the disk and -1 to terminate"<<endl<<endl;
    int x;
    cin>>x;

    if(x==1){
      int rid,rsize;
      cout<<"Give the Record ID and Size to be iserted ";
      cin>>rid>>rsize;
      if(rsize>ps){
        cout<<"Record Size must be smaller than page size"<<endl;
        continue;
      }
      if(DiskContent.FileStart==NULL){
        FirstPage = new Page(ps);
        DiskContent.FileStart=FirstPage;
        FirstPage->insert(rid,rsize);
      }
      else{
          Page* temp=DiskContent.FileStart;
          Page* prevtemp;
          int result=0;
          while(temp!=NULL){
            prevtemp=temp;
            result=temp->insert(rid,rsize);
            if(result==1) break;
            temp=temp->Next;
          }
          if(result==0){
            LastPage = new Page(ps);
            LastPage->Next=NULL;
            LastPage->Prev=prevtemp;
            prevtemp->Next=LastPage;
            LastPage->insert(rid,rsize);
          }
      }
    }
    else if(x==2){
      int rid;
      cout<<"Give the Record ID to search ";
      cin>>rid;
      if(DiskContent.FileStart==NULL){
        cout<<"Disk is Empty"<<endl<<endl;
        continue;
      }
      Page* temp=DiskContent.FileStart;
      int result=0;
      int dloc=0,ploc=-1;
      while(temp!=NULL){
        dloc++;
        result=temp->search(rid,&ploc);
        if(result==1) break;
        temp=temp->Next;
      }
      if(result==1){
        cout<<"Record is present in Page No. - "<<dloc<<" at the start index - "<<ploc<<endl<<endl;
      }
      else{
        cout<<"Record is not present"<<endl<<endl;
      }
    }
    else if(x==3){
      int rid;
      cout<<"Give the Record ID to be deleted ";
      cin>>rid;
      if(DiskContent.FileStart==NULL){
        cout<<"Disk is Empty"<<endl<<endl;
        continue;
      }
      Page* temp=DiskContent.FileStart;
      int result=0;
      int dloc=0,ploc=-1;
      while(temp!=NULL){
        dloc++;
        result=temp->deleterecord(rid,&ploc);
        if(result==1) break;
        temp=temp->Next;
      }
      if(result==1){
        cout<<"Record is Deleted from Page No. - "<<dloc<<" at the start index - "<<ploc<<endl<<endl;
      }
      else{
        cout<<"Record is not present"<<endl<<endl;
      }
    }
    else if(x==4){
      cout<<endl;
      DiskContent.displaydisk();
    }
    else if(x==-1){
      break;
    }
  }

return 0;

}
