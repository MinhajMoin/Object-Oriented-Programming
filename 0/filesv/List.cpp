#include "List.h"

List::List()
{
    start=NULL;
    end=NULL;
}

List::~List()
{
    while(start)
    {
        Node* tmp=start;
        start=start->next;
        delete tmp;
    }
    start=NULL;
    end=NULL;
}
List::List(const List& toCopy): start(NULL),end(NULL)
{
    for (int i=0; i<toCopy.size(); i++) //loop will iterate from 0 to size of toCopy and will append each element to the list being constructed
    {
        this->append(toCopy.getEntAtInd(i));
    }
}
int List::size() const
{
    int len=0;
    Node* tmp = start;
    while(tmp)
    {
        len++;
        tmp=tmp->next;
    }
    return len;
}
bool List::append(Entity* ent)
{

    if (start==NULL && end ==NULL)//if there are no elements in the queue
    {
        Node* p= new Node;
        if(p==NULL) return 0;
        p->ent=ent;
        start=p;
        end=p;
        //std::cout << "Object added to list.\n";
        return 1;
    }
    else
    {
        Node* p = new Node;
        if(p==NULL) return 0;
        p->ent=ent;
        end->next=p;
        p->prev=end;
        end=p;
        //std::cout << "Object added to list.\n";
        return 1;
    }
}
void List::clean()//deletes the first node whose alive has been set to 0, FIX
{
    Node* tmp=start;
    while(tmp)
    {
        if( !(tmp->ent->getAlive()) )
        {
            //cout << "removing index" << getNodeInd(tmp) << endl;
            removeNodeAtInd(getNodeInd(tmp));
            //removeNodeAtInd(i);
            break;
        }
        else
        {
            tmp=tmp->next;
        }

    }
}
bool List::removeNodeAtInd(int ind)
{
    if(ind<0 || ind>=this->size())
    {
        cerr<<"Invalid index passed  to removeNodeAtInd()"<<endl;
        return 0;
    }
    Node *behind = start;
    if(ind==0) //special case, if the ind to remove is 0
    {
        if(size()>1)
        {
            start = start->next;
            start->prev=NULL;
            delete behind;
            return 1;
        }
        else
        {
            delete start;
            start=NULL;
            end=NULL;
            return 1;
        }

    }
    else if(ind==size()-1)
    {
        cout << "Removing end" << endl;
        Node* tmp = end;
        end=end->prev;
        end->next=NULL;
        delete tmp;
        return 1;
    }
    else//general case, if the ind is > 0
    {
        cout << "LOL" << endl;
        //now go to the appropriate location
        Node* ahead  = behind->next;
        for (int i=1; i<ind; i++)
        {
            behind = ahead;
            ahead  = ahead->next;//at end of loop ahead will be storing the node at the given ind
        }
        behind->next = ahead->next;
        ahead->next->prev=behind;
        delete ahead;
        return 1;
    }
}

int List::getNodeInd(Node* toFind)
{
    int ind=0;
    Node* tmp=start;
    while(tmp)
    {
        if(tmp==toFind)
        {
            return ind;
        }
        else
        {
            ind++;
        }
        tmp=tmp->next;

    }
    //std::cout << "NOT FOUND IN GETNODEIND" << std::endl;
    return -1;
}
void List::empty()//Force empties current list, deletes all nodes and sets the list to inital condition
{
    for(int i=0; i<size(); i++)
    {
        this->removeNodeAtInd(0);
    }
    start=NULL;
    end=NULL;
}
void List::render(long int& frame, SDL_Renderer* gRenderer)
{
    Node* tmp=start;
    while(tmp)
    {
        tmp->ent->render(frame,gRenderer);
        tmp=tmp->next;
    }
}

Entity* List::getEntAtInd(int ind) const
{
    if(ind<0 || ind >=size()) return NULL;
    int i=0;
    Node*tmp=start;
    while(tmp)
    {
        if(i==ind)
        {
            return tmp->ent;
        }
        tmp=tmp->next;
        i++;
    }
    return NULL;
}
void List::move()
{
    Node* tmp=start;
    while(tmp)
    {
        if(tmp->ent->getType()==tmp->ent->MOBILEBRICKX || tmp->ent->getType()==tmp->ent->MOBILEBRICKY || tmp->ent->getType()==tmp->ent->PADDLE || tmp->ent->getType()==tmp->ent->BALL || tmp->ent->getType() == tmp->ent->BULLET || tmp->ent->getType()==tmp->ent->POWERUP)//check if the entity is movable
            tmp->ent->move(this);
        tmp=tmp->next;
    }
}

int List::getEntInd(Entity* toFind)//returns index of the given entity if found in one of the nodes of the list, -1 otherwise
{
    Node* tmp=start;
    int i=0;
    while(tmp)
    {
        if (tmp->ent == toFind)
        {
            return i;
        }
        else
        {
            tmp=tmp->next;
            i++;
        }
    }
    return -1;
}
Node* List::getNodeAtInd(int ind)
{
    if(ind<0 || ind >=size()) return NULL;
    int i=0;
    Node*tmp=start;
    while(tmp)
    {
        if(i==ind)
        {
            return tmp;
        }
        tmp=tmp->next;
        i++;
    }
    return NULL;
}

void List::resetEntities()
{
    Node* tmp=start;
    while(tmp)
    {
        tmp->ent->reset();
        tmp=tmp->next;
    }
}

int List::getBrickCount()
{
    int numBricks=0;//INVISIBLE and STEEL Bricks don't count, they're instead part of the level
    Node* tmp=start;
    while(tmp)
    {
        if(tmp->ent->getAlive())
        {


            if(tmp->ent->getType()==tmp->ent->ENTITIES::ONEHITBRICK)
            {
                numBricks++;
            }
            else if(tmp->ent->getType()==tmp->ent->ENTITIES::TWOHITBRICK)
            {
                numBricks++;
            }
            else if(tmp->ent->getType()==tmp->ent->ENTITIES::THREEHITBRICK)
            {
                numBricks++;
            }
            else if(tmp->ent->getType()==tmp->ent->ENTITIES::MOBILEBRICKX)
            {
                numBricks++;
            }
            else if(tmp->ent->getType()==tmp->ent->ENTITIES::MOBILEBRICKY)
            {
                numBricks++;
            }
        }
        tmp=tmp->next;
    }
    return numBricks;
}
